#include "GoalBase.h"


void GoalBase::add(Goal* goal)
{
    _goal_map.insert(std::make_pair(goal->_name, goal));
}

Goal* GoalBase::GetGoal(std::string goal_name) const
{
    return _goal_map.at(goal_name);
}