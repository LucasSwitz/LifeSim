#ifndef TILEMAP_H
#define TILEMAP_H

#include <streambuf>
#include <fstream>
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
            _tiles.emplace_back();
            for(int k = 0; k < current_vector.size(); k++)
            {
                int tile_id = current_vector.at(k);
                Tile* tile = LuaTileFactory::Instance()->GetTile(tile_id);
                tile->SetComponentValueFloat("Position","x",k*TILE_WIDTH);
                tile->SetComponentValueFloat("Position","y",i*TILE_HEIGHT);
                _tiles.at(i).push_back(tile);
            }
        }
    }

    //read in string, split on \n for row
    //split each column by space for vector
    //use load from vector
    void LoadFromFile(std::string file_path)
    {
        std::ifstream map_stream(file_path);
        std::string map_string;

        map_stream.seekg(0, std::ios::end);   
        map_string.reserve(map_stream.tellg());
        map_stream.seekg(0, std::ios::beg);

        map_string.assign((std::istreambuf_iterator<char>(map_stream)),std::istreambuf_iterator<char>());

        std::vector<std::string> rows = split(map_string, '\n');

        std::vector<std::vector<int>> map;

        for(auto& row_string : rows)
        {
            std::vector<std::string> split_row = split(row_string, ' ');
            std::vector<int> int_id_row;

            for(auto& string_id : split_row)
            {
                int_id_row.push_back(std::stoi(string_id));
            }
            map.push_back(int_id_row);
        }
        LoadFromVector(map);
    }
        //split helpers
    std::vector<std::string> split(const std::string &s, char delim) 
    {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }

    template<typename T>
    void split(const std::string &s, char delim, T result) 
    {
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            *(result++) = item;
        }
    }

    //add all tiles to CUB.
    void Show()
    {
        _active = true;

        for(auto it = _tiles.begin(); it != _tiles.end(); it++)
        {
            for(auto tile_it = (*it).begin(); tile_it != (*it).end(); tile_it++)
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
            for(auto tile_it = (*it).begin(); tile_it != (*it).end(); tile_it++)
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

    Tile* TileAt(int x, int y)
    {
        if(_tiles.empty())
            return nullptr;
        
        int row = y / TILE_HEIGHT;
        int column = x / TILE_WIDTH;

        return _tiles[row][column];
    }

    void Erase()
    {

    }

 private:
    std::vector<std::vector<Tile*>> _tiles;
    bool _active = false;
};
#endif