#ifndef TILE_H
#define TILE_H

#include "src/component/ComponentUser.h"

#define TILE_WIDTH 100
#define TILE_HEIGHT 100
class Tile : public ComponentUser
{
    public:
        Tile(int id){}
    private:
        int _id;
};

#endif