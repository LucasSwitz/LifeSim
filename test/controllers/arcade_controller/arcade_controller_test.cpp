#include "src/controllers/TBArcadeController.h"

int main()
{
    TBArcadeController controller(0);
    bool quit = false;

    struct pollfd ufds[1];
    unsigned char buf[CHUNK_SIZE];

    ufds[0].fd = STDIN_FILENO;
    ufds[0].events = POLLIN;

    while (!quit)
    {
        int rv = poll(ufds, 1, 100);
        if (rv == -1)
        {
            
        }
        else if (rv == 0)
        {
            printf("[Arcade Controller] | XAxis: %i | YAxis: %i | LeftButton: %i | RightButton: %i \n",
            controller.XAxis(), controller.YAxis(), controller.LeftButton(), controller.RightButton());
        }
        else
        {
            quit = true;
        }
    }
}