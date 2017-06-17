#include "ActionScriptFactory.h"

ActionScript* ActionScriptFactory::GetAction(std::string action_name, Actor* performer)
{
    ActionScript* new_action = new ActionScript(performer);
    std::string script_path = _action_map.at(action_name);
    new_action->LoadScript(LUA_STATE,script_path, action_name);
    return new_action;
}

//actions will all have capital names
void ActionScriptFactory::AddScript(Preamble& pre, std::string script_path)
{
    _action_map.insert(std::make_pair(pre.GetFlag("Name"), script_path));
}