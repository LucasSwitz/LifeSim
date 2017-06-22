#include "ScriptableSystem.h"

void ScriptableSystem::Update(double seconds_elapsed)
{
    if (_update_function)
        (*_update_function)(*_system_table, seconds_elapsed);
}

void ScriptableSystem::LoadScript(luabridge::lua_State *L, const std::string &script_path, const std::string &system_name)
{
    using namespace luabridge;
    _name = system_name;
    if (luaL_dofile(L, script_path.c_str()) == 0)
    {
        _system_table = std::make_shared<LuaRef>(getGlobal(L, system_name.c_str()));
        if (_system_table->isTable())
        {
            if((*_system_table)["Decorators"])
            {                
                LuaDecorated::LoadLuaDecorators(*_system_table,(*_system_table)["Decorators"]);
            }
            if ((*_system_table)["Update"].isFunction())
            {
                _update_function = std::make_unique<LuaRef>((*_system_table)["Update"]);
            }

            if ((*_system_table)["after"].isString())
            {
                _after = (*_system_table)["after"].cast<std::string>();
            }
        }
    }
    else
    {
        std::cout << "Error, can't open script: " << script_path << std::endl;
    }
}