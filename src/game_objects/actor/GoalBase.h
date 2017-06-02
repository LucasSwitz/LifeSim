#ifndef GOALBASE_H
#define GOALBASE_H

#include <unordered_map>
#include "src/game_objects/actor/Goal.h"

class GoalBase
{
public:
    static GoalBase* Instance()
    {
        static GoalBase intance;
        return &intance;
    }

    Goal* GetGoal(std::string goal_name) const;

    void add(Goal* goal);

private:
    GoalBase(){};
    std::unordered_map<std::string, Goal*> _goal_map;
};
#endif  