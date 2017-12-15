#ifndef LUATEST_H
#define LUATEST_H

#include <LuaBridge/LuaBridge.h>
#include <iostream>
#include <gtest/gtest.h>
#include "src/utils/lua/LuaBindings.h"
#include "src/utils/lua/LuaUniversal.h"
#include "src/utils/debug/DebugFlags.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

using namespace luabridge;

class LuaTest : public ::testing::Test
{
  public: 

    LuaTest()
    {
        LuaUniversal::Instance()->Init();
        DebugFlags::Instance()->Clear();
        LuaBindings::Bind(LUA_STATE);
        Globals::SetResourceRoot("/home/lucas/Desktop/LifeSim/res");
    }   

    void SetUp()
    {
        
    }
};

#endif