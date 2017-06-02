#ifndef ACTOR_H
#define ACTOR_H

#include <unordered_map>
#include "src/game_objects/Entity.h"
#include "src/game_objects/actor/GoalLog.h"

class Actor{

public:
    Actor(){};
    void AddGoal(std::string goal_name);
    void ApplyCondition(std::string condition_name);
    bool HasCondition(std:: string condition_name);
    void Tick();
    int GetHunger();

protected:
    unsigned short _age;
    unsigned short _health;
    unsigned short _hunger;
    std::unordered_map<std::string, int> _conditions;
    std::unordered_map<std::string, GoalLog*> _goals;

    void SetHunger(int hunger);
};

#endif