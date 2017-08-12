#ifndef LUAUNIVERSAL_H
#define LUAUNIVERSAL_H

#include <LuaBridge/LuaBridge.h>
#include <list>
#include <unordered_map>
#include <iostream>
#include <vector>


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

    static void StringListFromLuaTable(lua_State *L, std::list<std::string>& list)
    {
        int length = get_length(L, -1);
        for (int i = 0; i < length; i++)
        {
            lua_pushinteger(L, i + 1);
            lua_gettable(L, -2);
            if (lua_isstring(L, -1))
            {
                list.push_back(std::string(lua_tostring(L, -1)));
            }

            lua_pop(L, 1);
        }
    }

    static void IntListFromLuaTable(std::list<int>& list,lua_State *L)
    {
        int length = get_length(L, -1);
        for (int i = 0; i < length; i++)
        {
            lua_pushinteger(L, i + 1);
            lua_gettable(L, -2);
            if (lua_isnumber(L, -1))
            {
                list.push_back(lua_tointeger(L, -1));
            }
            lua_pop(L, 1);
        }
    }

    static void FloatVectorFromLuaTable(std::vector<float>& list,lua_State *L)
    {
        int length = get_length(L, -1);
        for (int i = 0; i < length; i++)
        {
            lua_pushinteger(L, i + 1);
            lua_gettable(L, -2);
            if (lua_isnumber(L, -1))
            {
                list.push_back(lua_tonumber(L, -1));
            }
            lua_pop(L, 1);
        }
    }

    template <typename T>
    static void ListFromTable(const LuaRef &table, std::list<T> &list)
    {
        if (table.isNil())
        {
            return;
        }

        auto L = table.state();
        push(L, table);

        lua_pushnil(L);
        while (lua_next(L, -2) != 0)
        {
            if (lua_isstring(L, -2))
            {
                list.push_back(LuaRef::fromStack(L, -1).cast<T>());
            }
            lua_pop(L, 1);
        }

        lua_pop(L, 1);
    }

  private:
    lua_State *L;
};
#endif