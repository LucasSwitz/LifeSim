#include <iostream>
#include "ActionScriptChain.h"
#include "src/game_objects/actor/actions/ActionFactory.h"

ActionScriptChain::ActionScriptChain(std::vector<std::string> scripts, Actor& performer)
{

    for(std::string script: scripts)
    {
        Action* action = ActionFactory::Instance()->GetAction(script, performer);
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
        _name = _current_action->GetName();
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

void ActionScriptChain::AddAction(Action* action)
{
    _action_queue.push(action);
}