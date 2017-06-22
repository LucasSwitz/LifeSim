#ifndef LUAENTITY_H
#define LUAENTITY_H

#include <iostream>
#include "src/game_objects/Entity.h"
#include "src/utils/lua/LuaUniversal.h"
#include "src/component/LuaComponent.h"
#include "src/decorator/LuaDecorated.h"
#include <unordered_map>

using namespace luabridge;
class LuaEntity : public Entity, public LuaDecorated
{
    public:
    void LoadScript(lua_State* lua_state, std::string script_path,std::string entity_name);

    void ConfigureAllComponentsFromLua(const LuaRef& ref);
};
#endif