#include "Actor.h"
#include "src/game_objects/actor/actions/Action.h"

void Actor::AddGoal(std::string goal_name)
{
    _goals.insert(std::make_pair(goal_name, new GoalLog(goal_name, *this)));
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

void Actor::AddToActionQueue(Action *action)
{
    _action_queue.push(action);
}

void Actor::Tick()
{
    if (!_goals.empty())
    {
        GoalBase::Instance()->GetGoal(_goals.begin()->second->goal_name)->Check(*this);
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

Action *Actor::GetCurrentAction()
{
    return _current_action;
}

void Actor::UpdateInternalValue(std::string key, int value)
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
