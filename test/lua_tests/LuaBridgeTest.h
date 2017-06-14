#include <LuaBridge/LuaBridge.h>
#include <iostream>
#include <gtest/gtest.h>

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

        virtual void SetUp()
        {   
            L = luaL_newstate();
            luaL_dofile(L, "../lua_scripts/script.lua");
            luaL_openlibs(L);
            lua_pcall(L, 0, 0, 0);
        }
};

TEST_F(LuaTest, LuaBridgeTest)
{
        LuaRef string_from_script = getGlobal(L, "testString");
        LuaRef num_from_script = getGlobal(L, "number");
        std::string read_string = string_from_script.cast<std::string>();
        int read_number = num_from_script.cast<int>();
        EXPECT_EQ(read_string, "LuaBridge Works!");
        EXPECT_EQ(read_number, 42);
}


TEST_F(LuaTest, TableTest)
{
    LuaRef table_ref = getGlobal(L, "window");
    LuaRef title_ref = table_ref["title"];
    LuaRef width_ref = table_ref["width"];
    LuaRef height_ref = table_ref["height"];
    std::string title_string = title_ref.cast<std::string>();
    int width = width_ref.cast<int>();
    int height = height_ref.cast<int>();

    EXPECT_EQ(title_string, "Window v.0.1");
    EXPECT_EQ(width, 400);
    EXPECT_EQ(height,500); 
}