#include "Entity.h"
#include "src/game_objects/EntityManager.h"
int Entity::_lastId = ENTITY_ID_START-1;
int Entity::CPP_DEFINED_ENTITY = 0;
int Entity::LUA_DEFINED_ENTITY = 1;

Entity::Entity(int type = 0, std::string prototype_name) : _type(type), _prototype_name(prototype_name)
{
    _lastId++;
    _id = _lastId;
    while(!EntityManager::Instance()->IDAvailable(_id))
        _id++;
    EntityManager::Instance()->RegisterEntity(this);
}

int Entity::ID() const
{
    return _id;
}

bool Entity::IsType(int type) const
{
    return type == _type;
}

std::string& Entity::GetPrototypeName()
{
    return _prototype_name;
}

void Entity::SetPrototypeName(std::string& name)
{
    _prototype_name = name;
}
//request a special ID number
void Entity::SetID(int id)
{
    if (id < 0)
        return;

    EntityManager::Instance()->DeregisterEntity(_id);
    _id = id;
    EntityManager::Instance()->RegisterEntity(this);
}

Entity::~Entity()
{

}