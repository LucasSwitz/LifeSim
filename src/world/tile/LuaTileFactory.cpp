#include "src/world/tile/LuaTileFactory.h"

void LuaTileFactory::AddScript(Preamble &pre, std::string script_path)
{
    int prototype_id = std::stoi(pre.GetFlag("ID"));
    std::string prototype_name = pre.GetFlag("Name");
    _tile_directory.insert(std::make_pair(prototype_id, script_path));
    _tile_id_to_name_directory.insert(std::make_pair(prototype_id, prototype_name));
    _tile_name_to_id_directory.insert(std::make_pair(prototype_name, prototype_id));
};

Tile *LuaTileFactory::GetTile(int id)
{
    if (!TilePrototypeExists(id))
    {
        throw AssetNotFoundException("Tile: " + std::to_string(id));
    }

    LuaTile *new_tile = new LuaTile(id, _tile_id_to_name_directory.at(id));

    new_tile->LoadScript(LUA_STATE, _tile_directory.at(id), _tile_id_to_name_directory.at(id));
    return new_tile;
}

Tile *LuaTileFactory::GetTile(std::string name)
{
    if (!TilePrototypeExists(name))
    {
        throw AssetNotFoundException("Tile: " + name);
    }

    return this->GetTile(_tile_name_to_id_directory.at(name));
}

bool LuaTileFactory::TilePrototypeExists(int id)
{
    return _tile_directory.find(id) != _tile_directory.end();
}

bool LuaTileFactory::TilePrototypeExists(std::string name)
{
    return _tile_name_to_id_directory.find(name) != _tile_name_to_id_directory.end();
}

void LuaTileFactory::Reset()
{
    _tile_directory.clear();
    _tile_name_to_id_directory.clear();
    _tile_id_to_name_directory.clear();
}

const std::unordered_map<int, std::string> &LuaTileFactory::GetAllTileIndentifiers()
{
    return _tile_id_to_name_directory;
}

const std::unordered_map<int, std::string> &LuaTileFactory::GetAllTiles()
{
    return _tile_directory;
}