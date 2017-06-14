#include <LuaBridge/LuaBridge.h>
#include <iostream>
#include <gtest/gtest.h>
#include "src/game_objects/actor/actions/ActionScriptFactory.h"
#include "src/utils/LuaBindings.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

using namespace luabridge;

class ActionScriptTest : public ::testing::Test
{
  public:
    lua_State *L;

    void SetUp()
    {
        L = luaL_newstate();
        luaL_openlibs(L);
        LuaBindings::Bind(L);
        
        ActionScriptFactory::Instance()->SetLuaState(L);
        ActionScriptFactory::Instance()->AddAction("ActionEat", "/home/pabu/Desktop/LifeSim/lua_scripts/actions/ActionEat.lua");
    }
};

TEST_F(ActionScriptTest, LuaBridgeTest)
{
    Actor *actor = new Actor();
    ActionScript *action = ActionScriptFactory::Instance()->GetAction("ActionEat", actor);
    action->Start();

    EXPECT_EQ(5,actor->GetInternalValue("Hunger"));
}