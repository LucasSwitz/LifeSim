#include <stddef.h>
#include <LuaBridge/LuaBridge.h>
#include <iostream>
#include <gtest/gtest.h>
#include "test/lua_tests/ActionScriptTest.h"
#include "src/game_objects/actor/actions/ActionScriptFactory.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
using namespace luabridge;

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

