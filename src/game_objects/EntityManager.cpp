#include "EntityManager.h"
#include "src/game_objects/Entity.h"


EntityManager* EntityManager::_instance = nullptr;


Entity *EntityManager::GetEntityByID(int id)
{
    auto it = _entity_map.find(id);

    if (it == _entity_map.end())
    {
        //TODO: Throw exception
    }

    return _entity_map.at(id);
}

void EntityManager::DeregisterEntity(int id)
{
    if(!IDAvailable(id))
        _entity_map.erase(_entity_map.find(id));
}

void EntityManager::RegisterEntity(Entity *entity)
{
    _entity_map.insert(std::make_pair(entity->_id, entity));
}

EntityManager* EntityManager::Instance()
{
    return _instance;
}

std::map<int, Entity *>& EntityManager::GetAllEntities()
{
    return _entity_map;
}

int EntityManager::GetNumberOfEntities()
{
    return _entity_map.size();
}

LuaList<Entity*>* EntityManager::AsLuaList()
{
    return LuaList<Entity*>::FromMapToLuaList<int, Entity*>(_entity_map);
}

bool EntityManager::IDAvailable(int id)
{
    return _entity_map.find(id) == _entity_map.end();
}

void EntityManager::Clear()
{
    _entity_map.clear();
}

EntityManager::~EntityManager()
{
    std::cout << "Cleaning up entities...." << std::endl;
    for(auto it = _entity_map.begin(); it != _entity_map.end(); it++)
    {
        if(it->second)
            delete it->second;
    }
}