#include "Entity.h"
#include "src/game_objects/EntityManager.h"
int Entity::_lastId = ENTITY_ID_START - 1;
int Entity::CPP_DEFINED_ENTITY = 0;
int Entity::LUA_DEFINED_ENTITY = 1;

Entity::Entity(int type, std::string prototype_name, int id) : _type(type), _prototype_name(prototype_name), _id(id)
{

    if (_id == -1)
    {
        _lastId++;
        _id = _lastId;

        while (!EntityManager::Instance()->IDAvailable(_id))
            _id++;
    }
}

int Entity::ID() const
{
    return _id;
}

bool Entity::IsType(int type) const
{
    return type == _type;
}

std::string &Entity::GetPrototypeName()
{
    return _prototype_name;
}

void Entity::SetPrototypeName(std::string &name)
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
}

Entity *Entity::Clone()
{
    Entity *e = new Entity(0, _prototype_name);
    std::unordered_map<std::string, Component *> components = GetAllComponents();
    for (auto it = components.begin(); it != components.end(); it++)
    {
        Component *c = new Component(*(it->second));
        e->AddComponent(c);
    }

    return e;
}

Entity::~Entity()
{
    if (EntityManager::Instance())
    {
        if (EntityManager::Instance()->Instance()->HasEntity(_id))
            EntityManager::Instance()->DeregisterEntity(_id);
    }
}