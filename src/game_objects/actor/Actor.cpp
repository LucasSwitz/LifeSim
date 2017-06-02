#include "Actor.h"

void Actor::AddGoal(std::string goal_name)
{
    _goals.insert(std::make_pair(goal_name,new GoalLog(goal_name,*this)));
}

void Actor::ApplyCondition(std::string condition_name)
{
    if(HasCondition(condition_name))
    {
        _conditions.at(condition_name)++;
    }
    else
    {
        _conditions.insert(std::make_pair(condition_name,1));
    }
}

bool Actor::HasCondition(std::string condition_name)
{
    return _conditions.find(condition_name) != _conditions.end();
}

void Actor::SetHunger(int hunger)
{
    _hunger = hunger;
}

int Actor::GetHunger()
{
    return _hunger;
}

void Actor::Tick()
{
    if(!_goals.empty())
    {
        GoalBase::Instance()->GetGoal(_goals.begin()->second->goal_name)->Check(*this);
    }
}