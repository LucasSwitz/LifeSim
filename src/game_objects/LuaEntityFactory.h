#ifndef LUAENTITYFACTORY_H
#define LUAENTITYFACTORY_Hs

#include "src/utils/ScriptFactory.h"

class LuaEntityFactory : public ScriptFactory<std::string>
{
  public:
    virtual void AddScript(Preamble &pre, std::string script_path) override
    {
        int prototype_id = std::stoi(pre.GetFlag("PrototypeID"));
        std::string prototype_name = pre.GetFlag("Name");

        _entity_scripts.insert(std::make_pair(prototype_id, script_path));
        _entity_name_to_id.insert(std::make_pair(prototype_name, prototype_id));
        _entity_id_to_name.insert(std::make_pair(prototype_id, prototype_name));
    };

    LuaEntity *GetEntity(int id)
    {
        LuaEntity *new_entity = new LuaEntity();
        new_entity->LoadScript(LUA_STATE, _entity_scripts.at(id), _entity_id_to_name.at(id));
        return new_entity;
    }

    LuaEntity *GetEntity(std::string name)
    {
        return this->GetEntity(_entity_name_to_id.at(name));
    }

    static LuaEntityFactory *Instance()
    {
        static LuaEntityFactory instance("/home/lucas/Desktop/LifeSim/lua_scripts/entities", "Entity");
        return &instance;
    }

  private:
    LuaEntityFactory(std::string path_to_scripts, std::string type) : ScriptFactory<std::string>(path_to_scripts, type){};

    std::map<int, std::string> _entity_scripts;
    std::unordered_map<std::string, int> _entity_name_to_id;
    std::unordered_map<int, std::string> _entity_id_to_name;
};

#endif