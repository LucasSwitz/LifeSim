#ifndef TILE_H
#define TILE_H

#include "components/ComponentUser.h"


#define TILE_WIDTH 100
#define TILE_HEIGHT 100
class Tile : public ComponentUser
{
    public:
        Tile(int identifier, std::string name_) : id(identifier), name(_name)
        {
            ComponenUserBase.Instance()->Register(this, "Graphics");
            ComponentUserBase.Instance()->Register(this, "Position");
        }
        
        int id;       
        std::string name;
};

#endif