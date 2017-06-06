#ifndef ACTIONCHAIN_H
#define ACTIONCHAIN_H

#include <queue>
#include <vector>
#include "src/game_objects/actor/actions/Action.h"

class ActionChain : public Action
{
public:
    ActionChain(){};
    ActionChain(std::vector<std::string> scripts, Actor& performer);
    void Start() override;
    void Perform() override;
    bool IsFinished() override;
    void AddAction(Action * action);

protected:
     Action* BuildFromScript(std::unordered_map<std::string, std::string> flags){};

private:
    std::queue<Action*> _action_queue;
    bool _is_finished = false;
    Action* _current_action = nullptr;

};
#endif