#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>
#include "src/utils/lua/LuaList.h"

#define Entity_Manager EntityManager::Instance()

/**
  Contains all entities. Entities can be accessed by the assigned ID.
**/
class Entity;

class EntityManager
{
  public:
    Entity *GetEntityByID(int id);

    void RegisterEntity(Entity* entity);

    static EntityManager* Instance();

    std::map<int, Entity*> GetAllEntities();

    int GetNumberOfEntities();

    LuaList<Entity*>* AsLuaList();

    void Clear();

    ~EntityManager();

  private:
    std::map<int, Entity *> _entity_map;
};

#endif