#ifndef LUADEFINEDASSET_H
#define LUADEFINEDASSET_H

#include "src/utils/Globals.h"

class LuaDefinedAsset
{
  public:
    void LoadScript(lua_State *lua_state, std::string script_path, const std::string &entity_name)
    {
        using namespace luabridge;

        if (luaL_dofile(lua_state, script_path.c_str()) == 0)
        {
            _LoadScript(lua_state, entity_name);
        }
        else
        {
            throw FailedToLoadAssetException(script_path + ": " + entity_name);
        }
    }

  protected:
    virtual void _LoadScript(lua_State *lua_state, const std::string &entity_name) = 0;
};
#endif