#include "GoalBase.h"
#include "src/game_objects/actor/goal/Goal.h"

void GoalBase::Add(Goal* goal)
{
    if(_goal_map.find(goal->_name) == _goal_map.end())
        _goal_map.insert(std::make_pair(goal->_name, goal));
}

Goal* GoalBase::GetGoal(std::string goal_name) const
{
    return _goal_map.at(goal_name);
}

void GoalBase::Erase()
{
    _goal_map.clear();
}