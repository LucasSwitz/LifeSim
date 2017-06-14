#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include "src/game_objects/actor/actions/ActionScript.h"
#include "src/game_objects/actor/Actor.h"
#include "src/utils/lua/LuaUniversal.h"

#include <unordered_map>

class ActionScriptFactory
{
public:
    ActionScript* GetAction(std::string action_script, Actor* performer);
    static ActionScriptFactory* Instance()
    {
        static ActionScriptFactory instance;
        return &instance;
    }

    void AddAction(std::string action_name, std::string script_name); //TODO:Make Protected

protected:

private:
    ActionScriptFactory(){};
    std::unordered_map<std::string, std::string> _action_map;
};

#endif
