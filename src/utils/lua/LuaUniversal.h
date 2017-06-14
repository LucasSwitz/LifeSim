#ifndef LUAUNIVERSAL_H
#define LUAUNIVERSAL_H

#include <LuaBridge/LuaBridge.h>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#define LUA_STATE LuaUniversal::Instance()->GetLuaState()

using namespace luabridge;

class LuaUniversal
{
public:
    
    lua_State* GetLuaState()
    {
        return L;
    }

    void Init()
    {
        L = luaL_newstate();
        luaL_openlibs(L);
    }

    static LuaUniversal* Instance()
    {
        static LuaUniversal instance;

        return &instance;
    }

    private:
         lua_State *L;

};
#endif