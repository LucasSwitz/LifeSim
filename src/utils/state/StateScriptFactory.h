#include <unordered_map>
#include "src/utils/ScriptibleState.h"
class StateScriptFactory
{

public:

    ScriptibleState* GetScriptibleState(std::string script_template_class, std::string script_name)
    {
        return _scripts_map.at(script_template_class).at(script_name);
    }

    void AddScriptibleState(std::string script_template_class, std::string script_name, ScriptibleState* state)
    {
        auto it = _scripts_map.at(script_template_class);
        if(it == _scripts_map.end())
        {
            std::unordered_map<std::string, ScriptibleState*> class_states;
            class_state.insert(std::make_pair(script_name, state));

            _scripts_map.insert(std::make_pair(script_template_name,class_states));
        }
        else
        {
            it->second.insert(std::make_pair(script_name, state));
        }
    }

    StateScriptFactory* Instance()
    {
        static StateScriptFactory instance;
        return &instance;
    }


private:
    std::unordered_map<std::string, std::unordered_map<std::string, ScriptibleState*>> _scripts_map;
}