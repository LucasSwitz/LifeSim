#ifndef TILEMAP_H
#define TILEMAP_H

#include <streambuf>
#include <fstream>
#include <algorithm>
#include <math.h>
#include "src/world/tile/Tile.h"
#include "src/world/tile/LuaTileFactory.h"

#define BLANK_TILE_SCRIPT "BlankTile"

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
        _file_name = file_path;
        
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

    void SaveToFile(std::string file_name)
    {
        _file_name = file_name;
    
        std::ofstream file_out(file_name);

        for(std::vector<Tile*>& vect : _tiles)
        {
            for(Tile* tile : vect)
            {
                file_out << tile->GetID();
                file_out << " ";
            }

            file_out << "\n";
        }

        file_out.close();
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
        int row = CoordToRow(x);
        int column = CoordToColumn(y);
        
        if(_tiles.empty() || row >= _tiles.size() || column >= _tiles[0].size())
            return nullptr;

        return _tiles[row][column];
    }

    void TilesInRange(int first_x, int first_y, int last_x, int last_y, std::list<Tile*>& tiles)
    {
        int first_row = CoordToRow(first_y);
        int last_row = CoordToRow(last_y);
        int first_column = CoordToColumn(first_x);
        int last_column = CoordToColumn(last_x);

        if(first_row > last_row)
            std::swap(first_row, last_row);
        
        if(first_column > last_column)
            std::swap(first_column, last_column);

        for(int i = first_row; i <= last_row; i++)
        {
            for(int k = first_column; k <= last_column; k++)
            {
                tiles.push_back(_tiles[i][k]);
            }
        }
    }

    static int CoordToColumn(int x)
    {
        return x / TILE_WIDTH;
    }

    static int CoordToRow(int y)
    {
        return y / TILE_HEIGHT;
    }

    void Blank(int width, int height)
    {
        for(int i =0; i < width; i++)
        {
            std::vector<Tile*> row;
            for(int k =0; k < height; k++)
            {
                Tile* tile = LuaTileFactory::Instance()->GetTile(BLANK_TILE_SCRIPT);
                tile->SetComponentValueFloat("Position","x",k*TILE_WIDTH+(TILE_WIDTH/2));
                tile->SetComponentValueFloat("Position","y",i*TILE_HEIGHT+ (TILE_HEIGHT/2));
                row.push_back(tile);
            }
            _tiles.push_back(row);
        }
    }

    std::string& GetFile()
    {
        return _file_name;
    }

    int HeightPx()
    {
        return _tiles.size()*TILE_HEIGHT;
    }

    int WidthPx()
    {
        return _tiles[0].size()*TILE_WIDTH;
    }

    void Erase()
    {
        for(auto it = _tiles.begin(); it != _tiles.end(); it++)
        {
            for(auto tile_it = (*it).begin(); tile_it != (*it).end(); tile_it++)
            {
                delete *tile_it;
            }
        }
    }

    ~TileMap()
    {
        Erase();
    }

 private:
    std::vector<std::vector<Tile*>> _tiles;
    std::string _file_name;
    bool _active = false;
};
#endif