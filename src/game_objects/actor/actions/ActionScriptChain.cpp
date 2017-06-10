#include "ActionScriptChain.h"
#include "src/game_objects/actor/actions/ActionScriptFactory.h"

ActionScriptChain::ActionScriptChain(Actor* performer,std::vector<std::string> action_names) :
    ActionScript(performer)
{
    for(std::string action_name: action_names)
    {
        ActionScript* action = ActionScriptFactory::Instance()->GetAction(action_name, performer);
        AddAction(action);
    }
}

void ActionScriptChain::Start()
{

}

void ActionScriptChain::Perform()
{

    if(!_current_action)
    {
        _current_action = _action_queue.front();
        _current_action->Start();
    }

    if(_current_action->IsFinished())
    { 
        _action_queue.pop();
    }
    else
    {
        _current_action->Perform();
    }
}

bool ActionScriptChain::IsFinished()
{
    return _action_queue.empty();
}

void ActionScriptChain::AddAction(ActionScript* action)
{
    _action_queue.push(action);
}

std::string ActionScriptChain::GetName()
{
    if(_current_action)
        return _current_action->GetName();
    return "Unnamed";
}