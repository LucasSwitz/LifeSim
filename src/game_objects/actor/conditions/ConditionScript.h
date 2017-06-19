#ifndef CONDITION_H
#define CONDITION_H

#include <memory>
#include "src/game_objects/actor/Actor.h"

class Condition
{
  public:
    void Start(Actor &t);

    void Update(Actor &t);

    void End(Actor &t);

    bool isFinished(Actor &t);

    static Condition* Instance();

    void LoadScript(luabridge::lua_State *L, const std::string &script_path, const std::string &condition_name);

  private:
    std::unique_ptr<luabridge::LuaRef> _start_function;
    std::unique_ptr<luabridge::LuaRef> _update_function;
    std::unique_ptr<luabridge::LuaRef> _is_finished_function;
    std::unique_ptr<luabridge::LuaRef> _end_function;
};
#endif