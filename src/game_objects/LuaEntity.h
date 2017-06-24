#ifndef LUAENTITY_H
#define LUAENTITY_H

#include <memory>
#include <iostream>

#include "src/game_objects/Entity.h"
#include "src/utils/lua/LuaUniversal.h"
#include "src/component/LuaComponent.h"
#include <unordered_map>

using namespace luabridge;
class LuaEntity : public Entity
{
    public:
    void LoadScript(lua_State* lua_state, std::string script_path,std::string entity_name);

    void ConfigureAllComponentsFromLua(const LuaRef& ref);

    void AddComponent(std::string name, const LuaRef& new_component) //only this gets exposed to lua
    {
        (*_entity_table)["Components"][name] = new_component; //i guess keep this updated for good measure.
        LuaComponent* c = new LuaComponent();
        c->FromLuaRef(new_component);

        ComponentUser::AddComponent(c);
    }

    void RemoveComponent(std::string name) //only this gets exposed to lua
    {
        (*_entity_table)["Components"][name] = nullptr; //i guess keep this updated for good measure.

        ComponentUser::RemoveComponent(name);
    }

    LuaRef& AsTable()
    {
        return *_entity_table;
    }

    private:
    std::shared_ptr<LuaRef> _entity_table;
};
#endif