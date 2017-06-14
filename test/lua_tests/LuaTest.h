#include <LuaBridge/LuaBridge.h>
#include <iostream>
#include <gtest/gtest.h>
#include "src/utils/LuaBindings.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

using namespace luabridge;

class LuaTest : public ::testing::Test
{
  public:
    lua_State *L;

    void SetUp()
    {
        L = luaL_newstate();
        luaL_openlibs(L);
        LuaBindings::Bind(L);
    }
};
