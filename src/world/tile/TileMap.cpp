#include "src/world/tile/TileMap.h"

void TileMap::LoadFromArray(int **map, int rows, int columns)
{
}

void TileMap::LoadFromVector(std::vector<std::vector<int>> map)
{
    for (int i = 0; i < map.size(); i++)
    {
        std::vector<int> current_vector = map.at(i);
        _tiles.emplace_back();
        for (int k = 0; k < current_vector.size(); k++)
        {
            int tile_id = current_vector.at(k);
            Tile *tile = LuaTileFactory::Instance()->GetTile(tile_id);
            tile->SetComponentValueFloat("Position", "x", k * TILE_WIDTH);
            tile->SetComponentValueFloat("Position", "y", i * TILE_HEIGHT);
            _tiles.at(i).push_back(tile);
        }
    }
}

//read in string, split on \n for row
//split each column by space for vector
//use load from vector
void TileMap::LoadFromFile(std::string file_path)
{
    std::cout << "Loading Tilemap From File: " << file_path << std::endl;
    _file_name = file_path;

    std::ifstream map_stream(file_path);
    std::string map_string;

    map_stream.seekg(0, std::ios::end);
    map_string.reserve(map_stream.tellg());
    map_stream.seekg(0, std::ios::beg);

    map_string.assign((std::istreambuf_iterator<char>(map_stream)), std::istreambuf_iterator<char>());

    std::vector<std::string> rows = split(map_string, '\n');

    std::vector<std::vector<int>> map;

    for (auto &row_string : rows)
    {
        std::vector<std::string> split_row = split(row_string, ' ');
        std::vector<int> int_id_row;

        for (auto &string_id : split_row)
        {
            int_id_row.push_back(std::stoi(string_id));
        }
        map.push_back(int_id_row);
    }
    LoadFromVector(map);
}

void TileMap::SaveToFile(std::string file_name)
{
    _file_name = file_name;

    std::ofstream file_out(file_name);

    for (std::vector<Tile *> &vect : _tiles)
    {
        for (Tile *tile : vect)
        {
            file_out << tile->GetID();
            file_out << " ";
        }

        file_out << "\n";
    }

    file_out.close();
}

//split helpers
std::vector<std::string> TileMap::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

template <typename T>
void TileMap::split(const std::string &s, char delim, T result)
{
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        *(result++) = item;
    }
}

//add all tiles to CUB.
void TileMap::Show()
{
    _active = true;

    for (auto it = _tiles.begin(); it != _tiles.end(); it++)
    {
        for (auto tile_it = (*it).begin(); tile_it != (*it).end(); tile_it++)
        {
            (*tile_it)->EnableAll();
        }
    }
}

//remove all tiles from CUB.
void TileMap::Hide()
{
    _active = false;

    for (auto it = _tiles.begin(); it != _tiles.end(); it++)
    {
        for (auto tile_it = (*it).begin(); tile_it != (*it).end(); tile_it++)
        {
            (*tile_it)->DisableAll();
        }
    }
}

bool TileMap::IsActive()
{
    return _active;
}

void TileMap::Unload()
{
    if (IsActive())
        Hide();

    //then delete all tiles
}

Tile *TileMap::TileAt(int x, int y)
{
    int row = CoordToRow(x);
    int column = CoordToColumn(y);

    if (_tiles.empty() || row >= _tiles.size() || column >= _tiles[0].size())
        return nullptr;

    return _tiles[row][column];
}

void TileMap::TilesInRange(int first_x, int first_y, int last_x, int last_y, std::list<Tile *> &tiles)
{
    int first_row = std::min((int)_tiles.size() - 1, CoordToRow(first_y));
    int last_row = std::min((int)_tiles.size() - 1, CoordToRow(last_y));
    int first_column = std::min((int)_tiles[0].size() - 1, CoordToColumn(first_x));
    int last_column = std::min((int)_tiles[0].size() - 1, CoordToColumn(last_x));

    if (first_row > last_row)
        std::swap(first_row, last_row);

    if (first_column > last_column)
        std::swap(first_column, last_column);

    for (int i = first_row; i <= last_row; i++)
    {
        for (int k = first_column; k <= last_column; k++)
        {
            tiles.push_back(_tiles[i][k]);
        }
    }
}

int TileMap::CoordToColumn(int x)
{
    return x / TILE_WIDTH;
}

int TileMap::CoordToRow(int y)
{
    return y / TILE_HEIGHT;
}

void TileMap::Blank(TileMap& map, int width, int height)
{
    for (int i = 0; i < width; i++)
    {
        std::vector<Tile *> row;
        for (int k = 0; k < height; k++)
        {
            Tile *tile = LuaTileFactory::Instance()->GetTile(BLANK_TILE_SCRIPT);
            tile->SetComponentValueFloat("Position", "x", k * TILE_WIDTH + (TILE_WIDTH / 2));
            tile->SetComponentValueFloat("Position", "y", i * TILE_HEIGHT + (TILE_HEIGHT / 2));
            row.push_back(tile);
        }
        map._tiles.push_back(row);
    }
}

std::string &TileMap::GetFile()
{
    return _file_name;
}

int TileMap::HeightPx()
{
    return _tiles.size() * TILE_HEIGHT;
}

int TileMap::WidthPx()
{
    return _tiles[0].size() * TILE_WIDTH;
}

void TileMap::Erase()
{
    for (auto it = _tiles.begin(); it != _tiles.end();)
    {
        for (auto tile_it = (*it).begin(); tile_it != (*it).end(); tile_it++)
        {
            delete *tile_it;
        }

        it = _tiles.erase(it);
    }
}

TileMap::~TileMap()
{
    Erase();
}
