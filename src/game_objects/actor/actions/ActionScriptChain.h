#ifndef ActionScriptChain_H
#define ActionScriptChain_H

#include <queue>
#include <vector>
#include "src/game_objects/actor/actions/ActionScript.h"

class ActionScriptChain : public ActionScript
{
public:
    ActionScriptChain(Actor* performer, std::vector<std::string> action_names);
    void Start() override;
    void Perform() override;
    bool IsFinished() override;
    std::string GetName() override;
    void AddAction(ActionScript * action);

private:
    std::queue<ActionScript*> _action_queue;
    bool _is_finished = false;
    ActionScript* _current_action = nullptr;

};
#endif