#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include "src/game_objects/actor/actions/ActionScript.h"
#include "src/game_objects/actor/Actor.h"
#include "src/utils/lua/LuaUniversal.h"
#include "src/utils/ScriptFactory.h"
#include <unordered_map>

class ActionScriptFactory : public ScriptFactory<std::string>
{
public:
    ActionScript* GetAction(std::string action_script, Actor* performer);
    static ActionScriptFactory* Instance()
    {
        static ActionScriptFactory instance;
        return &instance;
    }

    void AddScript(Preamble& pre, std::string script_name) override; //TODO:Make Protected

protected:

private:
    ActionScriptFactory() : ScriptFactory<std::string>("/home/pabu/Desktop/LifeSim/lua_scripts/actions", "Action"){};
    std::unordered_map<std::string, std::string> _action_map;
};

#endif
