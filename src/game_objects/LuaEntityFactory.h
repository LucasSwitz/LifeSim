#ifndef LUAENTITYFACTORY_H
#define LUAENTITYFACTORY_H

#include "src/utils/ScriptFactory.h"

/**
    Factory for creating entity instances from their Lua prototypes.
**/

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

    LuaEntity* GetEntity(int id)
    {
        if(!EntityPrototypeExists(id))
        {
            std::cout << "Entity Does Not Exists: " << id << std::endl;
            return nullptr;
        }

        LuaEntity *new_entity = new LuaEntity();
        new_entity->LoadScript(LUA_STATE, _entity_scripts.at(id), _entity_id_to_name.at(id));
        return new_entity;
    }

    LuaEntity *GetEntity(std::string name)
    {
        if(!EntityPrototypeExists(name))
        {   
            std::cout << "Entity Does Not Exists: " << name << std::endl;
            return nullptr;
        }
        
        return this->GetEntity(_entity_name_to_id.at(name));
    }

    static LuaEntityFactory *Instance()
    {
        static LuaEntityFactory instance("/home/pabu/Desktop/LifeSim/lua_scripts/entities", "Entity");
        return &instance;
    }

    bool EntityPrototypeExists(int id)
    {
        return _entity_scripts.find(id) != _entity_scripts.end();
    }


    bool EntityPrototypeExists(std::string name)
    {
        return _entity_name_to_id.find(name) != _entity_name_to_id.end();
    }

    void Reset() override
    {
        _entity_scripts.clear();
        _entity_id_to_name.clear();
        _entity_id_to_name.clear();
    }

  private:
    LuaEntityFactory(std::string path_to_scripts, std::string type) : ScriptFactory<std::string>(path_to_scripts, type){};

    std::map<int, std::string> _entity_scripts;
    std::unordered_map<std::string, int> _entity_name_to_id;
    std::unordered_map<int, std::string> _entity_id_to_name;
};

#endif