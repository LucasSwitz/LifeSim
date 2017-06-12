#include "Actor.h"
#include "src/game_objects/actor/actions/ActionScript.h"
#include "src/game_objects/actor/goal/GoalScript.h"
#include "src/game_objects/actor/actions/ActionScriptFactory.h"

void Actor::AddGoal(std::string goal_name)
{
    _goals.push_back(GoalBase::Instance()->GetGoal(goal_name));
}

void Actor::ApplyCondition(std::string condition_name)
{
    if (HasCondition(condition_name))
    {
        _conditions.at(condition_name)++;
    }
    else
    {
        _conditions.insert(std::make_pair(condition_name, 1));
    }
}

bool Actor::HasCondition(std::string condition_name)
{
    return _conditions.find(condition_name) != _conditions.end();
}

void Actor::AddToActionQueue(std::string action_name)
{
    _action_queue.push(ActionScriptFactory::Instance()->GetAction(action_name, this));
}

void Actor::Tick()
{
    if (!_goals.empty())
    {   
        _goals.at(0)->Check(*this);
    }
    DoActions();
}

void Actor::DoActions()
{
    if (!_action_queue.empty())
    {
        if (!_current_action)
        {
            _current_action = _action_queue.front();

            _current_action->Start();
        }

        if (_current_action->IsFinished())
        {
            _action_queue.pop();
        }
        else
        {
            _current_action->Perform();
        }
    }
}

ActionScript* Actor::GetCurrentAction()
{
    return _current_action;
}

void Actor::SetInternalValue(std::string key, int value)
{
    auto it = _internal_values.find(key);
    if (it == _internal_values.end())
    {
        _internal_values.insert(std::make_pair(key, value));
    }
    else
    {
        it->second = value;
    }
}

int Actor::GetInternalValue(std::string key) const
{
    auto it = _internal_values.find(key);
    if (it == _internal_values.end())
    {    
        return 0;
    }

    return it->second;
}
