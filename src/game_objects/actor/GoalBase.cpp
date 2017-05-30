#include "src/game_object/actor/GoalBase.h"


void GoalBase::add(Goal* goal)
{
    _goal_map.insert<std::make_pair<std::string, Goal*>(goal->_name, goal)>;
}

void GoalBase::GetGoal(std::string goal_name)
{
        return _goal_map.at(goal_name);
}