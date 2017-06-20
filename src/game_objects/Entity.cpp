#include "Entity.h"
#include "src/game_objects/EntityManager.h"
int Entity::_lastId = -1;

Entity::Entity()
{
    _lastId++;
    _id = _lastId;
    EntityManager::Instance()->RegisterEntity(this);
}

bool Entity::HasAttribute(std::string name)
{
    return _attributes.find(name) != _attributes.end();
}

int Entity::GetAttribute(std::string name)
{
    if (HasAttribute(name))
        return _attributes.at(name);
    else
        return 0;
}

void Entity::AddAttribute(std::string name, int value)
{
    auto it = _attributes.find(name);
    if (it == _attributes.end())
        _attributes.insert(std::make_pair(name, value));
    else
        it->second = value;
}

int Entity::ID() const
{
    return _id;
}

Component *Entity::GetComponent(std::string name)
{
    return _components.at(name);
}

void Entity::AddComponent(Component *component)
{
    _components.insert(std::make_pair(component->GetName(), component));
}

void Entity::RemoveComponent(std::string name)
{

}

void Entity::SetID(int id)
{
    if (id < 0)
        return;

    _id = id;
}

bool Entity::HasComponent(std::string name)
{
    return _components.find(name) != _components.end();
}

Entity::~Entity()
{
    for(auto it = _components.begin(); it != _components.end(); it++)
    {
        delete it->second;
    }
}