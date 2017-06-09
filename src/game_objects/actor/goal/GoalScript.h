#ifndef GOALLOG_H
#define GOALLOG_H

#include "src/game_objects/actor/goal/GoalBase.h"
//#include "src/game_objects/actor/goal/Goal.h"


class Actor;
class GoalScript
{
public:
    GoalScript(std::string goal_name_, Actor& actor_) : goal_name(goal_name_), actor(actor_){};
    bool operator < (const GoalLog& goal_log);
    std::string goal_name;
    Actor& actor;
};
#endif