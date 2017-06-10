#ifndef GOALLOG_H
#define GOALLOG_H

#include <memory>
#include <iostream>

#include <LuaBridge/LuaBridge.h>
#include "src/game_objects/actor/goal/GoalBase.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class Actor;
class GoalScript
{
    friend class GoalBase;
   public:

   void Start(Actor& actor);
   bool IsFullfilled(Actor& actor);
   void End(Actor& actor);
   int Priority(Actor& actor);
   void Check(Actor& actor);

  protected:
    GoalScript();

    void LoadScript(luabridge::lua_State *L, const std::string &script_path, const std::string &goal_name)
    {
        using namespace luabridge;
        if (luaL_dofile(L, script_path.c_str()) == 0)
        {
            LuaRef goal_table = getGlobal(L, goal_name.c_str());
            if (goal_table.isTable())
            {
                if (goal_table["Start"].isFunction())
                {
                    start_function = std::make_unique<LuaRef>(goal_table["Start"]);
                }

                if (goal_table["Check"].isFunction())
                {
                    check_function = std::make_unique<LuaRef>(goal_table["Check"]);
                }

                if (goal_table["End"].isFunction())
                {
                    end_function = std::make_unique<LuaRef>(goal_table["End"]);
                }

                if (goal_table["IsFullfilled"].isFunction())
                {
                    is_fullfilled_function = std::make_unique<LuaRef>(goal_table["IsFullfilled"]);
                }

                if (goal_table["Priority"].isFunction())
                {
                    priority_function = std::make_unique<LuaRef>(goal_table["Priority"]);
                }
            }
        }
        else
        {
            std::cout << "Error, can't open script!" << std::endl;
        }
    };

  private:
    std::unique_ptr<luabridge::LuaRef> start_function;
    std::unique_ptr<luabridge::LuaRef> check_function;
    std::unique_ptr<luabridge::LuaRef> priority_function;
    std::unique_ptr<luabridge::LuaRef> is_fullfilled_function;
    std::unique_ptr<luabridge::LuaRef> end_function;
};

#endif