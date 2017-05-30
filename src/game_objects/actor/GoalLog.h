#ifndef GOALLOG_H
#define GOALLOG_H

#include "src/game_objects/actor/GoalBase.h"

template <typename T>
class GoalLog
{
public:
    GoalLog(std::string goal_name, T& actor) : _goal_name(goal_name), _actor(actor){};

private:
    std::string _goal_name;
    T& _actor;
};
#endif