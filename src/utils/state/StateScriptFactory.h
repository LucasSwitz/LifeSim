#ifndef STATESCRIPTFACTORY_H
#define STATESCRIPTFACTORY_H

#include <unordered_map>
#include <iostream>
#include "src/utils/state/ScriptableState.h"
#include "src/utils/ScriptFactory.h"
#include "src/utils/LuaUniversal.h"

class StateScriptFactory : public ScriptFactory<ScriptableState>
{

public:

    ScriptableState* GetScriptableState(std::string script_template_class, std::string script_name)
    {
        ScriptableState* s= _scripts_map.at(script_template_class).at(script_name);

        return _scripts_map.at(script_template_class).at(script_name);
    }

    ScriptableState* Configure(std::string full_script_path, std::string script_name)
    {
        ScriptableState* new_state = new ScriptableState();
        new_state->LoadScript(LUA_STATE, full_script_path, script_name);
        return new_state;
    }

    static StateScriptFactory* Instance()
    {
        static StateScriptFactory instance("/home/pabu/Desktop/LifeSim/lua_scripts/state", "State");
        return &instance;
    }


private:
    StateScriptFactory(std::string script_path, std::string state_name) : ScriptFactory<ScriptableState>(script_path, state_name){};
};

#endif