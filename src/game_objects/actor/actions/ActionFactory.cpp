#include "ActionFactory.h"

Action* ActionFactory::_GetAction(ActionDescriptor descriptor, Actor& performer)
{
    if(_action_map.find(descriptor.action) == _action_map.end())
    {
        return nullptr; 
    }

    Action* action = BuildActionFromScript(descriptor.action, descriptor.flags);
    action->_performer = &performer;

    return action;
}

Action* ActionFactory::GetAction(std::string script, Actor& performer)
{
    ActionDescriptor d(script);
    return _GetAction(d, performer);
}

void ActionFactory::AddAction(Action* action)
{
    _action_map.insert(std::make_pair(action->_name,action));
}

Action* ActionFactory::BuildActionFromScript(std::string action_name, std::unordered_map<std::string, std::string> flags)
{
    Action* action = _action_map.at(action_name)->BuildFromScript(flags);
    return action;
}