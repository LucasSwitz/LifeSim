#ifndef TBArcadeControllerPacket_h
#define TBArcadeControllerPacket_h

class TBArcadeControllerPacket
{

  public:
    static TBArcadeControllerPacket Deserialize(const unsigned char *data)
    {
        TBArcadeControllerPacket p;
        p.x_axis = data[0];
        p.y_axis = data[1];
        p.button_left = data[2];
        p.button_right = data[3];

        return p;
    }

    unsigned char x_axis = 0;
    unsigned char y_axis = 0;
    unsigned char button_left = 0;
    unsigned char button_right = 0;
    TBArcadeControllerPacket(){};
};
#endif