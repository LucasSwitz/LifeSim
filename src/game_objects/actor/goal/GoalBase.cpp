#include "GoalBase.h"
#include "src/game_objects/actor/goal/GoalScript.h"


/**
need class that will go through goals, load their scripts, and add them to goalbase
**/
void GoalBase::Add(std::string goal_name, GoalScript* goal)
{
    if(_goal_map.find(goal_name) == _goal_map.end())
        _goal_map.insert(std::make_pair(goal_name, goal));
}

GoalScript* GoalBase::GetGoal(std::string goal_name) const
{
    return _goal_map.at(goal_name);
}

void GoalBase::Erase()
{
    _goal_map.clear();
}