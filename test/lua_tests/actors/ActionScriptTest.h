#include <iostream>
#include "src/game_objects/actor/actions/ActionScriptFactory.h"
#include "test/lua_tests/lua_core/LuaTest.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}


class ActionScriptTest : public LuaTest
{
  public:
    Actor *actor;

    ActionScriptTest()
    {
        ActionScriptFactory::Instance()->PopulateFactory();
    }
    void SetUp()
    {   
        actor = new Actor();
    }
};

TEST_F(ActionScriptTest, LuaBridgeTest)
{
    ActionScript *action = ActionScriptFactory::Instance()->GetAction("ActionEat", actor);
    action->Start();
    EXPECT_EQ(5,actor->GetInternalValue("Hunger"));
}