#ifndef LUAENTITY_H
#define LUAENTITY_H

#include <iostream>
#include "src/game_objects/Entity.h"
#include "src/utils/lua/LuaUniversal.h"
#include "src/component/LuaComponent.h"
#include <unordered_map>

using namespace luabridge;
class LuaEntity : public Entity
{
    public:
    void LoadScript(lua_State* lua_state, std::string script_path,std::string entity_name)
    {
        using namespace luabridge;

        if (luaL_dofile(lua_state, script_path.c_str()) == 0)
        {
            LuaRef entity_table = getGlobal(lua_state, entity_name.c_str());
            if (entity_table.isTable())
            {
                if(entity_table["Components"])
                {
                    ConfigureAllComponentsFromLua(entity_table["Components"]);
                }

                if(entity_table["ID"])
                {
                    SetID(entity_table["ID"].cast<int>());
                }
            }
        }
        else
        {
            std::cout << "Error, can't open script: " << script_path << std::endl;
        }
    }

    void ConfigureAllComponentsFromLua(const LuaRef& ref)
    {
        std::unordered_map<std::string, LuaRef> components = LuaUniversal::KeyValueMapFromTable(ref);
        for(auto it : components)
        {
           auto key = it.first;
           LuaRef component_ref = it.second;

           LuaComponent* new_component = new LuaComponent(key);
           new_component->ConfigureFromLua(component_ref);
           AddComponent(new_component);
        }
    }
};
#endif