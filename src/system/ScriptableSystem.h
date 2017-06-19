#ifndef SCRIPTABLESYSTEM_H
#define SCRIPTABLESYSTEM_H

#include <memory>
#include <iostream>
#include "src/utils/lua/LuaUniversal.h"
#include "src/system/System.h"

class ScriptableSystem : public System
{
    public:
    ScriptableSystem(){};

    void Update(double seconds_elapsed) override;

    void LoadScript(luabridge::lua_State *L, const std::string &script_path, const std::string &system_name);

private:
        std::unique_ptr<luabridge::LuaRef> _update_function;
        std::unique_ptr<luabridge::LuaRef> _system_table;
};
#endif