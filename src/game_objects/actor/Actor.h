#ifndef ACTOR_H
#define ACTOR_H

#include <unordered_map>
#include <queue>

#include "src/game_objects/Entity.h"
#include "src/game_objects/actor/goal/GoalScript.h"


class ActionScript;
class ActionScriptFactory;

class Actor : public Entity{

public:
    Actor(){};
    void AddGoal(std::string goal_name);
    void ApplyCondition(std::string condition_name);
    bool HasCondition(std:: string condition_name);
    void Tick();
    void AddToActionQueue(std::string action_name);
    ActionScript* GetCurrentAction();
    void SetInternalValue(std::string key, int value);
    int GetInternalValue(std::string key) const;

protected:
    ActionScript* _current_action = nullptr;
    std::unordered_map<std::string, int> _conditions;
    std::vector<GoalScript*> _goals;

    std::queue<ActionScript*> _action_queue;

    std::unordered_map<std::string, int> _internal_values;

private:
    void DoActions();
};

#endif