#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>
#include <set>
#include "src/utils/lua/LuaList.h"
#include "src/event/EventSubscriber.h"
#include "src/event/Event.h"
#include "src/event/EventType.h"
#include "src/event/messaging/MessageDispatch.h"
#include "src/game_objects/LuaEntityFactory.h"

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

  EntityManager(const EntityManager& manager)
  {
    const std::map<int, Entity*>& entities = manager.GetAllEntities();

    for(auto it = entities.begin(); it != entities.end(); it++)
    {
      Entity* e = new Entity(*it->second);
      RegisterEntity(e);
    }
  }

  void RegisterEntity(Entity *entity);
  Entity *GetEntityByID(int id);
  void DeregisterEntity(int id);

  const std::map<int, Entity *>& GetAllEntities() const;
  int GetNumberOfEntities();

  Entity* GetNewest();

  void Clear();
  bool IDAvailable(int id);
  bool HasEntity(int id);

  LuaList<Entity *> *AsLuaList();

  std::list<Subscription> GetSubscriptions();
  void OnEvent(Event &e);

  void MarkForDelete(Entity* e);
  void Clean();

  static void GiveOwnership(EntityManager *instance)
  {
    _instance = instance;
    MessageDispatch::Instance()->RegisterSubscriber(_instance);
  }

private:
  std::map<int, Entity *> _entity_map;
  static EntityManager *_instance;
  std::set<Entity*> _delete_set;
};

#endif