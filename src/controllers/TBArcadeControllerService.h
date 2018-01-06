#ifndef TBARCADECONTROLLERSERVICE_H
#define TBARCADECONTROLLERSERVICE_H

#define PATH "/usr/share/tb"
#define SERVER_PATH "/usr/share/tb/controller.server"

#include "src/utils/ipc/UnixDomainSocket.h"
#include "src/controllers/TBArcadeControllerPacket.h"

class TBArcadeControllerService : public UnixDomainSocketListener
{
  public:
    TBArcadeControllerService() : _controller_socket(SERVER_PATH, PATH) {}
    void Start()
    {
        _controller_socket.SetDataListener(this);
        _controller_socket.StartAsync();
    }

    void Stop()
    {
        _controller_socket.Close();
    }

    bool Connected()
    {
        
    }

    const TBArcadeControllerPacket Get()
    {   
        return _packet;
    }

    void OnData(const unsigned char * data, const DomainSocket::exception& e) override
    {
        if(e.id)
            return;

        _packet = TBArcadeControllerPacket::Deserialize(data);
    }

  private:
    TBArcadeControllerPacket _packet;
    UnixDomainSocket _controller_socket;
};

#endif