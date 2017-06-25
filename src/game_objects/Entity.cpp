#include "Entity.h"
#include "src/game_objects/EntityManager.h"
int Entity::_lastId = -1;
int Entity::CPP_DEFINED_ENTITY = 0;
int Entity::LUA_DEFINED_ENTITY = 1;

Entity::Entity(int type = 0) : _type(type)
{
    _lastId++;
    _id = _lastId;
    EntityManager::Instance()->RegisterEntity(this);
}

int Entity::ID() const
{
    return _id;
}

bool Entity::IsType(int type)
{
    return type == _type;
}

void Entity::SetID(int id)
{
    if (id < 0)
        return;

    _id = id;
}

Entity::~Entity()
{

}