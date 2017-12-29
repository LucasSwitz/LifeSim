#ifndef LUATILE_H
#define LUATILE_H
#include "src/world/tile/Tile.h"
#include "src/utils/lua/LuaUniversal.h"
#include "src/component/LuaComponent.h"
#include "src/utils/lua/LuaDefinedAsset.h"
/**
    Purpose: Tile defined by a Lua file.
**/
class LuaTile : public Tile, public LuaDefinedAsset
{

  public:
    LuaTile(int id, std::string name) : Tile(id, name) {}
    virtual ~LuaTile(){};

    void ConfigureAllComponentsFromLua(const LuaRef &ref)
    {
        std::unordered_map<std::string, LuaRef> components = LuaUniversal::KeyValueMapFromTable(ref);
        for (auto it : components)
        {
            auto key = it.first;
            LuaRef component_ref = it.second;
            ptr<LuaComponent> new_component(new LuaComponent(key));
            new_component->FromLuaRef(component_ref);
            ComponentUser::AddComponent(new_component); // Tile will not immediately be added to CUB.
                                                        // TileMap will have to enable them
        }
    }

  protected:
    void _LoadScript(lua_State *lua_state, const std::string &tile_name)
    {
        LuaRef tile_table = getGlobal(lua_state, tile_name.c_str());

        if ((tile_table)["Components"])
        {
            LuaRef components_table = (tile_table)["Components"];
            ConfigureAllComponentsFromLua(components_table);
        }
    }
};
#endif