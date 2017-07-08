#ifndef TILEMAP_H
#define TILEMAP_H

#include "src/world/Tile.h"
/* Manges all tiles currently in memory*/\

class TileMap
{
 public:

    void LoadFromArray(int[][] map)
    {

    }

    void LoadFromFile(std::string file_path)
    {

        // Set Position of Each tile
    }

    void Load()
    {
        // Add Tiles to component user base
    }

    void Unload()
    {
        //Remove Tiles from ComponentUserBase
    }

    void Erase()
    {

    }

 private:
    std::vector<std::vector<Tile*>> _tiles;
};
#endif