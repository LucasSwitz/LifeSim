#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>
#include "src/utils/lua/LuaList.h"

#define Entity_Manager EntityManager::Instance()

class Entity;

class EntityManager
{
  public:
    Entity *GetEntityByID(int id)
    {
        auto it = _entity_map.find(id);

        if (it == _entity_map.end())
        {
            //TODO: Throw exception
        }

        return _entity_map.at(id);
    }

    void RegisterEntity(Entity* entity)
    {
        _entity_map.insert(std::make_pair(entity->_id, entity));
    }


    static EntityManager* Instance()
    {
        static EntityManager instance;
        return &instance;
    }

    std::map<int, Entity*> GetAllEntities()
    {
        return _entity_map;
    }

    int GetNumberOfEntities()
    {
        return _entity_map.size();
    }

    LuaList<Entity>* AsLuaList()
    {
        return LuaList<Entity>::FromMapToLuaList<int, Entity>(_entity_map);
    }

    void Clear()
    {
        _entity_map.clear();
    }

    ~EntityManager()
    {
        for(auto it = _entity_map.begin(); it != _entity_map.end(); it++)
        {
            delete it->second;
        }
    }

  private:
    std::map<int, Entity *> _entity_map;
};

#endif