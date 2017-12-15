#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>
#include <set>
#include "src/utils/lua/LuaList.h"
#include "src/event/EventSubscriber.h"
#include "src/event/Event.h"
#include "src/event/EventType.h"
#include "src/event/EventManager.h"
#include "src/game_objects/LuaEntityFactory.h"
#include "src/component/ComponentUserBase.h"
#include "src/event/messaging/MessageDispatcher.h"
/**
  Contains all entities. Entities can be accessed by the assigned ID.
**/
class Entity;

class EntityManager : public EventSubscriber, public MessageDispatcher
{
  friend class GameState;

public:
  ~EntityManager();
  EntityManager();

  EntityManager(const EntityManager& manager, ComponentUserBase& component_user_base)
  {
    const std::map<int, Entity*>& entities = manager.GetAllEntities();

    for(auto it = entities.begin(); it != entities.end(); it++)
    {
      Entity* e = new Entity(*it->second);
      e->EnableAll(component_user_base);
      _entity_map.insert(std::make_pair(e->_id, e));
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

  int Size();

  LuaList<Entity *> *AsLuaList();

  std::list<Subscription> GetSubscriptions();
  void OnEvent(Event &e);

  void MarkForDelete(Entity* e);
  void Clean();

private:
  std::map<int, Entity *> _entity_map;
  static EntityManager *_instance;
  std::set<Entity*> _delete_set;
};

#endif