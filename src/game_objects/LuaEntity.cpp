#include "LuaEntity.h"

void LuaEntity::_LoadScript(lua_State *lua_state, const std::string &entity_name)
{
    using namespace luabridge;
    SetPrototypeName(entity_name);

    _entity_table = std::make_shared<LuaRef>(getGlobal(lua_state, entity_name.c_str()));
    if ((*_entity_table).isTable())
    {
        if ((*_entity_table)["id"])
        {
            SetID((*_entity_table)["id"].cast<int>());
        }
        else
        {
            (*_entity_table)["id"] = this->ID();
        }

        if ((*_entity_table)["Components"])
        {
            LuaRef components_table = (*_entity_table)["Components"];
            ConfigureAllComponentsFromLua(components_table);
        }
    }
}

void LuaEntity::ConfigureAllComponentsFromLua(const LuaRef &ref)
{
    std::unordered_map<std::string, LuaRef> components = LuaUniversal::KeyValueMapFromTable(ref);
    for (auto it : components)
    {
        auto key = it.first;
        LuaRef component_ref = it.second;

        ptr<LuaComponent> new_component(new LuaComponent(key));
        new_component->FromLuaRef(component_ref);
        ComponentUser::AddComponent(new_component);
    }
}

LuaEntity::~LuaEntity()
{
}