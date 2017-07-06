#ifndef TILEMAP_H
#define TILEMAP_H


/* Manges all tiles currently in memory*/\

class TileMap
{
 public:
 
    void LoadFromArray(int[][] maps)
    {

    }

    void LoadFromFile(std::string file_path)
    {

    }

    void Erase()
    {

    }

 private:
    std::vector<std::vector<Tile*>> _tiles;
};
#endif