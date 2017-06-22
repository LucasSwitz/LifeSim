#include "Entity.h"
#include "src/game_objects/EntityManager.h"
int Entity::_lastId = -1;

Entity::Entity()
{
    _lastId++;
    _id = _lastId;
    EntityManager::Instance()->RegisterEntity(this);
}

int Entity::ID() const
{
    return _id;
}

void Entity::SetID(int id)
{
    if (id < 0)
        return;

    _id = id;
}

Entity::~Entity()
{
    for(auto it = _components.begin(); it != _components.end(); it++)
    {
        delete it->second;
    }
}