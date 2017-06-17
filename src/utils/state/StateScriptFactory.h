#ifndef STATESCRIPTFACTORY_H
#define STATESCRIPTFACTORY_H

#include <unordered_map>
#include <iostream>
#include "src/utils/state/ScriptableState.h"
#include "src/utils/ScriptFactory.h"
#include "src/utils/lua/LuaUniversal.h"

class StateScriptFactory : public ScriptFactory<ScriptableState>
{

public:

    ScriptableState* GetScriptableState(std::string script_template_class, std::string script_name)
    {
        if(_scripts_map.find(script_template_class) == _scripts_map.end() 
        || _scripts_map.at(script_template_class).find(script_name) == 
        _scripts_map.at(script_template_class).end())
        {
            std::cout << "Invalid Scriptable State: " << script_template_class << " , " << script_name << std::endl; 
        }

        ScriptableState* s= _scripts_map.at(script_template_class).at(script_name);

        return _scripts_map.at(script_template_class).at(script_name);
    }

    ScriptableState* Configure(std::string full_script_path, std::string scriptable_name)
    {
        ScriptableState* new_state = new ScriptableState();
        new_state->LoadScript(LUA_STATE, full_script_path, scriptable_name);
        return new_state;
    }

    void AddScript(Preamble& pre, ScriptableState *scriptable_object)
    {

        auto it = _scripts_map.find(pre.GetFlag("StateOwner"));
        if (it == _scripts_map.end())
        {
            std::unordered_map<std::string, ScriptableState *> class_states;
            class_states.insert(std::make_pair(pre.GetFlag("Name"), scriptable_object));
            _scripts_map.insert(std::make_pair(pre.GetFlag("StateOwner"), class_states));
        }
        else
        {
            it->second.insert(std::make_pair(pre.GetFlag("Name"), scriptable_object));
        }
    }

    static StateScriptFactory* Instance()
    {
        static StateScriptFactory instance("/home/lucas/Desktop/LifeSim/lua_scripts", "State");
        return &instance;
    }


private:
    StateScriptFactory(std::string script_path, std::string state_name) : ScriptFactory<ScriptableState>(script_path, state_name){};
    std::unordered_map<std::string, std::unordered_map<std::string, ScriptableState*>> _scripts_map;
};

#endif