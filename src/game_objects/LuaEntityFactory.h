#ifndef LUAENTITYFACTORY_H
#define LUAENTITYFACTORY_Hs

#include "src/utils/ScriptFactory.h"

class LuaEntityFactory : public ScriptFactory<LuaEntity>
{
    virtual LuaEntity* Configure(std::string script_path, std::string scriptable_name)
    {
        LuaEntity* new_entity = new LuaEntity();
        new_entity->LoadScript(LUA_STATE, script_path, scriptable_name);
        return new_entity;
    };

    virtual void AddScript(Preamble& pre, LuaEntity* entity)
    {
        int prototype_id = std::stoi(pre.GetFlag("PrototypeId"));
        _entity_prototypes.insert(prototype_id, entity);
        _entity_name_to_prototype_id(entity->GetName(), prototype_id);
    };

    LuaEntity* GetEntity(int id)
    {
        return _entity_prototypes.at(id).clone();
    }

    LuaEntity* GetEntity(std::string name)
    {
        return this->GetEntity(_entity_name_to_prototype_id(name));
    }

    static LuaEntityFactory* Instance()
    {
        static LuaEntityFactory instance("/home/lucas/Desktop/LifeSim/lua_scripts", "State");
        return &instance;
    }

private:
    LuaEntityFactory(std::string path_to_scripts) : ScriptFactory<LuaEntity>(path_to_scripts){};
    std::map<int, LuaEntity* > _entity_prototypes;
    std::unordered_map<std::string, int> _entity_name_to_prototype_id;

};

#endif