#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>

#define GET_ENTITY(int) EntityManager::Instance()->GetEntityByID(int)

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

    void RegisterEntity(Entity& entity)
    {
        _entity_map.insert(std::make_pair(entity._id, &entity));
    }

    static EntityManager* Instance()
    {
        static EntityManager instance;
        return &instance;
    }

  private:
    std::map<int, Entity *> _entity_map;
};

#endif