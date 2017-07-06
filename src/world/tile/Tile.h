#ifndef TILE_H
#define TILE_H

#include "components/ComponentUser.h"

class Tile : public ComponentUser
{
    public:
        Tile(int identifier, std::string name_) : id(identifier), name(_name){}
        
        int id;       
        std::string name;
};

#endif