#include "LuaEntity.h"

void LuaEntity::LoadScript(lua_State *lua_state, std::string script_path, std::string entity_name)
{
    using namespace luabridge;

    if (luaL_dofile(lua_state, script_path.c_str()) == 0)
    {
        LuaRef entity_table = getGlobal(lua_state, entity_name.c_str());
        if (entity_table.isTable())
        {
            if (entity_table["id"])
            {
                SetID(entity_table["id"].cast<int>());
            }
            else
            {
                entity_table["id"] = this->ID();
            }

             LuaDecorated::LoadLuaDecorators(entity_table);
        }
    }
    else
    {
        std::cout << "Error, can't open script: " << script_path << std::endl;
    }
}