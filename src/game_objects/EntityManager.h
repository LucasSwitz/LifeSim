#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>
#include "src/utils/lua/LuaList.h"
#include "src/event/EventSubscriber.h"
#include "src/event/Event.h"
#include "src/event/EventType.h"
#include "src/event/messaging/MessageDispatch.h"

#define Entity_Manager EntityManager::Instance()
/**
  Contains all entities. Entities can be accessed by the assigned ID.
**/
class Entity;

class EntityManager : public EventSubscriber
{
  friend class GameState;

public:
  static EntityManager *Instance();
  ~EntityManager();
  EntityManager();

  void RegisterEntity(Entity *entity);
  Entity *GetEntityByID(int id);
  void DeregisterEntity(int id);

  std::map<int, Entity *> &GetAllEntities();
  int GetNumberOfEntities();

  void Clear();
  bool IDAvailable(int id);
  bool HasEntity(int id);

  LuaList<Entity *> *AsLuaList();

  std::list<Subscription> GetSubscriptions();
  void OnEvent(Event &e);

  static void GiveOwnership(EntityManager *instance)
  {
    _instance = instance;
    MessageDispatch::Instance()->RegisterSubscriber(_instance);
  }

private:
  std::map<int, Entity *> _entity_map;
  static EntityManager *_instance;
};

#endif