#ifndef SCRIPTABLESYSTEM_H
#define SCRIPTABLESYSTEM_H

#include <memory>
#include <iostream>
#include "src/utils/lua/LuaUniversal.h"
#include "src/system/System.h"

class ScriptableSystem : public System
{
    public:

    void Update(double seconds_elapsed) override
    {   
        if(_update_function)
            (*_update_function)(seconds_elapsed);
    }

   void LoadScript(luabridge::lua_State *L, const std::string &script_path, const std::string &system_name)
    {
        using namespace luabridge;
        _name = system_name;

        if (luaL_dofile(L, script_path.c_str()) == 0)
        {
            LuaRef system_table = getGlobal(L, system_name.c_str());
            if (system_table.isTable())
            {
                if (system_table["Update"].isFunction())
                {
                    _update_function = std::make_unique<LuaRef>(system_table["Update"]);
                }

                if (system_table["after"].isString())
                {
                    _after = system_table["after"].cast<std::string>();
                }
            }
        }
        else
        {
            std::cout << "Error, can't open script: " << script_path << std::endl;
        }
    }

private:
        std::unique_ptr<luabridge::LuaRef> _update_function;
};
#endif