#include "src/world/tile/LuaTileFactory.h"

void LuaTileFactory::AddScript(Preamble &pre, std::string script_path)
{
    int prototype_id = std::stoi(pre.GetFlag("PrototypeID"));
    std::string prototype_name = pre.GetFlag("Name");

    _tile_directory.insert(std::make_pair(prototype_id, script_path));
    _tile_id_to_name_directory.insert(std::make_pair(prototype_id, prototype_name));
    _tile_name_to_id_directory.insert(std::make_pair(prototype_name, prototype_id));
};

Tile* LuaTileFactory::GetTile(int id)
{
    if(!TilePrototypeExists(id))
    {
        std::cout << "Tile Does Not Exists: " << id << std::endl;
        return nullptr;
    }

    LuaTile *new_tile = new LuaTile(id);
    new_tile->LoadFromFile(LUA_STATE, _tile_directory.at(id), _tile_id_to_name_directory.at(id));
    return new_tile;
}

Tile* LuaTileFactory::GetTile(std::string name)
{
    if(!TilePrototypeExists(name))
    {   
        std::cout << "Tile Does Not Exists: " << name << std::endl;
        return nullptr;
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