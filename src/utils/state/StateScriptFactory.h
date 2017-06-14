#ifndef STATESCRIPTFACTORY_H
#define STATESCRIPTFACTORY_H

#include <unordered_map>
#include "src/utils/state/ScriptableState.h"
#include <iostream>

class StateScriptFactory
{

public:

    ScriptableState* GetScriptableState(std::string script_template_class, std::string script_name)
    {
        ScriptableState* s= _scripts_map.at(script_template_class).at(script_name);

        return _scripts_map.at(script_template_class).at(script_name);
    }

    void AddScriptableState(std::string script_template_class, std::string script_name, ScriptableState* state)
    {
        auto it = _scripts_map.find(script_template_class);
        if(it == _scripts_map.end())
        {
            std::unordered_map<std::string, ScriptableState*> class_states;
            class_states.insert(std::make_pair(script_name, state));

            _scripts_map.insert(std::make_pair(script_template_class,class_states));
        }
        else
        {
            it->second.insert(std::make_pair(script_name, state));
        }
    }

    static StateScriptFactory* Instance()
    {
        static StateScriptFactory instance;
        return &instance;
    }


private:
    std::unordered_map<std::string, std::unordered_map<std::string, ScriptableState*>> _scripts_map;
};

#endif