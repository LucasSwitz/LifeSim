#ifndef ACTOR_H
#define ACTOR_H

#include <unordered_map>
#include <queue>

#include "src/game_objects/Entity.h"
#include "src/game_objects/actor/goal/GoalLog.h"

class Action;

class Actor : public Entity{

public:
    Actor(){};
    void AddGoal(std::string goal_script);
    void ApplyCondition(std::string condition_name);
    bool HasCondition(std:: string condition_name);
    void Tick();
    void AddToActionQueue(std::string action_script);
    Action* GetCurrentAction();
    void UpdateInternalValue(std::string key, int value);
    int GetInternalValue(std::string key) const;

protected:
    Action* _current_action = nullptr;
    std::unordered_map<std::string, int> _conditions;
    std::unordered_map<std::string, GoalLog*> _goals;

    std::queue<Action*> _action_queue;

    std::unordered_map<std::string, int> _internal_values;

private:
    void DoActions();
};

#endif