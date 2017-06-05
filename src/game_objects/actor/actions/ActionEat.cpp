#include "ActionEat.h"
#include "src/game_objects/actor/Actor.h"

void ActionEat::Start()
{
    if(!_target)
    {
        _isFinished = true;
    }
}

void ActionEat::Perform()
{
    int added_hunger = 0;
    if(_target->HasAttribute("Nutrition"))
    {
        added_hunger = _target->GetAttribute("Nutrition");
    }

    _performer->UpdateInternalValue("Hunger", added_hunger);
    _isFinished = true;
}

bool ActionEat::IsFinished()
{
    return _isFinished;
}

Action* ActionEat::BuildFromScript(std::unordered_map<std::string, std::string> flags)
{
    ActionEat * action = new ActionEat();
    action->_target = EntityManager::Instance()->GetEntityByID(std::stoi(flags.at("id")));
    return action;
}