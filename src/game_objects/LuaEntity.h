#ifndef LUAENTITY_H
#define LUAENTITY_H

#include <memory>
#include <iostream>

#include "src/game_objects/Entity.h"
#include "src/utils/lua/LuaUniversal.h"
#include "src/component/LuaComponent.h"
#include <unordered_map>

using namespace luabridge;

/**
    Entity object that is built from a LuaReference. Overrides many of Entity meathods.
    Components added to a LuaEntity will be added to the given LuaRef as well. This may change
    in the future.
**/
class LuaEntity : public Entity
{
    public:

    LuaEntity() : Entity(Entity::LUA_DEFINED_ENTITY,"")
    {
        
    };

    void LoadScript(lua_State* lua_state, std::string script_path,std::string& entity_name);

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

    static LuaEntity* DownCastFromEntity(Entity* e)
    {
        return dynamic_cast<LuaEntity*>(e);
    }

    void SetNumber(std::string component_name, std::string value_name, float value)
    {
         LuaRef comps = ((*_entity_table)["Components"]);
         LuaRef comp = comps[component_name];
         comp[value_name] = value;

        ComponentUser::SetComponentValueFloat(component_name, value_name, value);
    }

    void CallFunction(std::string component_name, std::string function_name)
    {
        LuaRef comps = (*_entity_table)["Components"];
        LuaRef comp = comps[component_name];
        LuaRef func = comp[function_name];
        (func)(this);
    }

    LuaRef& AsTable()
    {
        return *_entity_table;
    }

    private:
    std::shared_ptr<LuaRef> _entity_table;
};
#endif