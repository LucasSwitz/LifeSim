#ifndef GOALBASE_H
#define GOALBASE_H

#include <unordered_map>

class GoalScript;

class GoalBase
{
public:
    static GoalBase* Instance()
    {
        static GoalBase intance;
        return &intance;
    }

    GoalScript* GetGoal(std::string goal_name) const;

    void Add(std::string goal_name, GoalScript* goal);
    void Erase();

    //goals will be loaded into goal base, and their singletons will have static pointers to each scripts function

private:
    GoalBase(){};
    std::unordered_map<std::string, GoalScript*> _goal_map;
};
#endif  