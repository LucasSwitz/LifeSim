#include "Entity.h"
#include "src/game_objects/EntityManager.h"

int Entity::_lastId = ENTITY_ID_START - 1;
int Entity::CPP_DEFINED_ENTITY = 0;
int Entity::LUA_DEFINED_ENTITY = 1;

Entity::Entity(int type, std::string prototype_name, int id) : ComponentUser(CU_TYPE_ENTITY,id), 
        _type(type), _prototype_name(prototype_name)
{
    
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

Entity *Entity::Clone()
{
    Entity *e = new Entity(0, _prototype_name);
    auto components = GetAllComponents();
    for (auto it = components.begin(); it != components.end(); it++)
    {
        ptr<Component> c (new Component(*(it->second)));
        e->AddComponent(c);
    }

    return e;
}

Entity* Entity::DowncastFromComponentUser(ComponentUser* caster)
{
    Entity* e = dynamic_cast<Entity*>(caster);
    if(e)
        return e;
    return nullptr;
}

void Entity::SetInstance(int instance_id)
{
    _instance = instance_id;
}

int Entity::GetInstance() const
{
    return _instance;
}

void Entity::SetID(int id)
{
    _id = id;
}

Entity::~Entity()
{
    
}