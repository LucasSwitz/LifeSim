#include <iostream>
#include "src/game_objects/actor/actions/ActionScriptFactory.h"
#include "test/lua_tests/LuaTest.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}


class ActionScriptTest : public LuaTest
{
  public:
    Actor *actor;
    void SetUp()
    {   
        actor = new Actor();
        ActionScriptFactory::Instance()->AddAction("ActionEat", "/home/pabu/Desktop/LifeSim/lua_scripts/actions/ActionEat.lua");
    }
};

TEST_F(ActionScriptTest, LuaBridgeTest)
{
    ActionScript *action = ActionScriptFactory::Instance()->GetAction("ActionEat", actor);
    action->Start();

    EXPECT_EQ(5,actor->GetInternalValue("Hunger"));
}