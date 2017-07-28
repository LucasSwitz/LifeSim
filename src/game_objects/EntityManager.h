#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>
#include "src/utils/lua/LuaList.h"
#include "src/event/EventSubscriber.h"

#define Entity_Manager EntityManager::Instance()
/**
  Contains all entities. Entities can be accessed by the assigned ID.
**/
class Entity;

class EntityManager : public EventSubscriber
{
  friend class GameState;

public:
  static EntityManager* Instance();
  ~EntityManager();

  void RegisterEntity(Entity *entity);
  Entity *GetEntityByID(int id);
  void DeregisterEntity(int id);

  std::map<int, Entity *> &GetAllEntities();
  int GetNumberOfEntities();

  void Clear();
  bool IDAvailable(int id);
  bool HasEntity(int id);

  LuaList<Entity *> *AsLuaList();

  static void GiveOwnership(EntityManager *instance)
  {
      _instance = instance;
  }

private:
  std::map<int, Entity *> _entity_map;
  static EntityManager *_instance;
};

#endif