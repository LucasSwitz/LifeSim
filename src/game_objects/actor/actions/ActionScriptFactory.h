#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include "src/game_objects/actor/actions/Action.h"
#include "src/game_objects/actor/actions/ActionDescriptor.h"
#include "src/game_objects/actor/Actor.h"

#include <unordered_map>

class ActionScriptFactory
{
public:
    Action* GetAction(std::string action_script, Actor& performer);
    static ActionScriptFactory* Instance()
    {
        static ActionFactory instance;
        return &instance;
    }

    void AddAction(Action* action); //TODO:Make Protected


protected:

private:
    ActionFactory(){};
    Action* _GetAction(ActionDescriptor, Actor& performer);
    Action* BuildActionFromScript(std::string action_name, std::unordered_map<std::string, std::string> flags);

    std::unordered_map<std::string, Action*> _action_map;
};

#endif
