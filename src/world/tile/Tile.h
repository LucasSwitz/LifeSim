#ifndef TILE_H
#define TILE_H

#include "src/component/ComponentUser.h"

#define TILE_WIDTH 32
#define TILE_HEIGHT 32
class Tile : public ComponentUser
{
    public:
        Tile(int id){}
    private:
        int _id;
};

#endif