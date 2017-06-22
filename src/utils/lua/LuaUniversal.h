#ifndef LUAUNIVERSAL_H
#define LUAUNIVERSAL_H

#include <LuaBridge/LuaBridge.h>
#include <unordered_map>

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
    lua_State *GetLuaState()
    {
        return L;
    }

    void Init()
    {
        L = luaL_newstate();
        luaL_openlibs(L);
    }

    static LuaUniversal *Instance()
    {
        static LuaUniversal instance;

        return &instance;
    }

     static std::unordered_map<std::string, luabridge::LuaRef> KeyValueMapFromTable(const luabridge::LuaRef &table)
    {
        std::unordered_map<std::string, LuaRef> result;
        if (table.isNil())
        {
            return result;
        }

        auto L = table.state();
        push(L, table); // push table

        lua_pushnil(L); // push nil, so lua_next removes it from stack and puts (k, v) on stack
        while (lua_next(L, -2) != 0)
        { // -2, because we have table at -1
            if (lua_isstring(L, -2))
            { // only store stuff with string keys
                result.emplace(lua_tostring(L, -2), LuaRef::fromStack(L, -1));
            }
            lua_pop(L, 1); // remove value, keep key for lua_next
        }

        lua_pop(L, 1); // pop table
        return result;
    }

    template<typename T>
    static std::list<T> ListFromTable(const LuaRef& table)
    {
        std::unordered_map<std::string, LuaRef> result;
        if (table.isNil())
        {
            return result;
        }

        auto L = table.state();
        push(L, table); 

        lua_pushnil(L); 
        while (lua_next(L, -2) != 0)
        { 
            if (lua_isstring(L, -2))
            {
                result.push_back(LuaRef::fromStack(L, -1).cast<T>());
            }
            lua_pop(L, 1);
        }

        lua_pop(L, 1); 
        return result;
    }

  private:
    lua_State *L;
};
#endif