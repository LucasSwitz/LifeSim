#ifndef TILEMAP_H
#define TILEMAP_H

#include "src/world/tile/Tile.h"
#include "src/world/tile/LuaTileFactory.h"

/* Manges all tiles currently in memory*/
class TileMap
{
 public:

    void LoadFromArray(int** map, int rows, int columns)
    {

    }

    void LoadFromVector(std::vector<std::vector<int>> map)
    {
        for(int i = 0; i < map.size(); i++)
        {
            std::vector<int> current_vector = map.at(i);
            for(int k =0; k < current_vector.size(); k++)
            {
                int tile_id = current_vector.at(k);
                Tile* tile = LuaTileFactory::Instance()->GetTile(tile_id);
                tile->SetComponentValueFloat("Position","x",k*TILE_WIDTH);
                tile->SetComponentValueFloat("Position","y",i*TILE_HEIGHT);
                _tiles.at(i).push_back(tile);
            }
        }
    }

    void LoadFromFile(std::string file_path)
    {
        //read file int 2D vector
    }

    //add all tiles to CUB.
    void Show()
    {
        _active = true;

        for(auto it = _tiles.begin(); it != _tiles.end(); it++)
        {
            for(auto tile_it = (*it).begin(); tile_it != (*it).end(); it++)
            {
                (*tile_it)->EnableAll();
            }
        }
    }

    //remove all tiles from CUB.
    void Hide()
    {
        _active = false;

        for(auto it = _tiles.begin(); it != _tiles.end(); it++)
        {
            for(auto tile_it = (*it).begin(); tile_it != (*it).end(); it++)
            {
                (*tile_it)->DisableAll();
            }
        }
    }

    bool IsActive()
    {
        return _active;
    }

    void Unload()
    {
        if(IsActive())
            Hide();

        //then delete all tiles    
    }

    void Erase()
    {

    }

 private:
    std::vector<std::vector<Tile*>> _tiles;
    bool _active = false;
};
#endif