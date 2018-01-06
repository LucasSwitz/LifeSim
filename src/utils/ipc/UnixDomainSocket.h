#ifndef UNIXDOMAINSOCKET_H
#define UNIXDOMAINSOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <string>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/un.h>
#include <thread>
#include <sys/poll.h>

#define CHUNK_SIZE 1024
#define POLL_TIMEOUT 100

namespace DomainSocket
{
    struct exception
    {
        exception(int _id, const std::string &_msg) : id(_id), msg(_msg) {}

        int id;
        std::string msg;
    };
}

class UnixDomainSocketListener
{
  public:
    virtual void OnData(const unsigned char *data, const DomainSocket::exception &e) = 0;
};

class UnixDomainSocket
{

  public:
    const int TIMEOUT_EXN = 1;
    const int POLL_FAILED_EXN = 2;

    UnixDomainSocket(const std::string &server_path, const std::string &client_path, const std::string &client_name = "")
        : _server_path(server_path),
          _client_path(client_path),
          _client_name(client_name)
    {
        if (_client_name.empty())
        {
            _client_name = std::to_string(getpid());
        }
    }

    void StartAsync()
    {
        Start();
        _read_thread = std::thread(&UnixDomainSocket::Read, this);
    }

    void Start()
    {
        int rc, len;
        struct sockaddr_un server_sockaddr;
        struct sockaddr_un _client_socketaddr;
        memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
        memset(&_client_socketaddr, 0, sizeof(struct sockaddr_un));

        _client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
        if (_client_socket == -1)
        {
            printf("SOCKET ERROR = %s\n", strerror(errno));
            exit(1);
        }

        _client_socketaddr.sun_family = AF_UNIX;

        _client_addr =  _client_path + "/" + _client_name;

        strcpy(_client_socketaddr.sun_path, _client_addr.c_str());
        len = sizeof(_client_socketaddr);

        unlink(_client_addr.c_str());

        printf("Attemping to bind on address: %s \n", _client_addr.c_str());
        rc = bind(_client_socket, (struct sockaddr *)&_client_socketaddr, len);
        if (rc == -1)
        {
            printf("BIND ERROR: %s\n", strerror(errno));
            close(_client_socket);
            exit(1);
        }

        server_sockaddr.sun_family = AF_UNIX;
        strcpy(server_sockaddr.sun_path, _server_path.c_str());

        printf("Attempting to connect to server at: %s \n", server_sockaddr.sun_path);
        rc = connect(_client_socket, (struct sockaddr *)&server_sockaddr, len);
        if (rc == -1)
        {
            printf("CONNECT ERROR = %s\n", strerror(errno));
            close(_client_socket);
            exit(1);
        }
    }

    void SetDataListener(UnixDomainSocketListener *listener)
    {
        _listener = listener;
    }

    void Read()
    {
        struct pollfd ufds[1];
        unsigned char buf[CHUNK_SIZE];

        ufds[0].fd = _client_socket;
        ufds[0].events = POLLIN;

        int rv = poll(ufds, 1, 100);

        if (rv == -1)
        {
            perror("poll");
            UpdateListener(buf, DomainSocket::exception(POLL_FAILED_EXN, "Polling failed."));
        }
        else if (rv == 0)
        {
            UpdateListener(buf, DomainSocket::exception(TIMEOUT_EXN, "Poll timeout."));
        }
        else
        {
            if (ufds[0].revents & POLLIN)
            {
                int read = recv(_client_socket, buf, CHUNK_SIZE, 0);
                UpdateListener(buf, DomainSocket::exception(0, "No Exception."));
            }
        }
    }

    void Close()
    {
        if (_read_thread.joinable())
        {
            _read_thread.join();
        }

        printf("Closing Domain Socket Client: %s...\n", _client_name);
        unlink(_client_addr.c_str());
        close(_client_socket);
    }

    int FD()
    {
        return _client_socket;
    }

  private:
    std::string _server_path;
    std::string _client_path;
    std::string _client_name;
    std::string _client_addr;
    int _client_socket;
    std::thread _read_thread;
    bool _reading = false;
    UnixDomainSocketListener *_listener = nullptr;

    void UpdateListener(const unsigned char *data, const DomainSocket::exception &e)
    {
        if (_listener)
        {
            _listener->OnData(data, e);
        }
    }
};

#endif