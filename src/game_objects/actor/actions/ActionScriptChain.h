#ifndef ACTIONCHAIN_H
#define ACTIONCHAIN_H

#include <queue>
#include <vector>
#include "src/game_objects/actor/actions/ActionScript.h"

class ActionScriptChain : public ActionScript
{
public:
    ActionScriptChain(){};
    ActionScriptChain(std::vector<std::string> scripts, Actor& performer);
    void Start() override;
    void Perform() override;
    bool IsFinished() override;
    void AddAction(Action * action);

private:
    std::queue<Action*> _action_queue;
    bool _is_finished = false;
    Action* _current_action = nullptr;

};
#endif