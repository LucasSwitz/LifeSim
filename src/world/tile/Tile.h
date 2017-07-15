#ifndef TILE_H
#define TILE_H

#include "src/component/ComponentUser.h"

#define TILE_WIDTH 32
#define TILE_HEIGHT 32
class Tile : public ComponentUser
{
    public:
        Tile(int id, std::string name): _id(id), _name(name){}
        int GetID()
        {
            return _id;
        }
        std::string GetName()
        {
            return _name;
        }
    private:
        int _id;
        std::string _name;
};

#endif