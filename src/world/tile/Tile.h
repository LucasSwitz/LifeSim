#ifndef TILE_H
#define TILE_H

#include "src/component/ComponentUser.h"

#define TILE_WIDTH 256
#define TILE_HEIGHT 256
class Tile : public ComponentUser
{
    public:
        Tile(int id){}
    private:
        int _id;
};

#endif