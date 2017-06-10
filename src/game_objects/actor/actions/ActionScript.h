#ifndef ACTION_H
#define ACTION_H

#include <unordered_map>
#include <memory>
#include <iostream>

#include <LuaBridge/LuaBridge.h>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class Actor;
class ActionScriptFactory;

class ActionScript
{
    friend class ActionScriptFactory;

  public:
    ActionScript(Actor* performer);

    virtual void Start();

    virtual void Perform();

    virtual bool IsFinished();

    virtual std::string GetName();

  protected:
    void LoadScript(luabridge::lua_State *L, const std::string &script_path, const std::string &action_name);

  private:
    Actor* _performer;
    std::unique_ptr<luabridge::LuaRef> start_function;
    std::unique_ptr<luabridge::LuaRef> perform_function;
    std::unique_ptr<luabridge::LuaRef> is_finished_function;

    std::string _action_name = "null";
};

#endif