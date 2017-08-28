#include "EntityManager.h"
#include "src/game_objects/Entity.h"

EntityManager *EntityManager::_instance = nullptr;

EntityManager::EntityManager()
{
}

Entity *EntityManager::GetEntityByID(int id)
{
    auto it = _entity_map.find(id);

    if (it == _entity_map.end())
    {
        std::cout << "No Entity With id: " << id << std::endl;
        return nullptr;
    }

    return _entity_map.at(id);
}

void EntityManager::DeregisterEntity(int id)
{
    if (!IDAvailable(id))
        _entity_map.erase(_entity_map.find(id));
}

void EntityManager::RegisterEntity(Entity *entity)
{
    _entity_map.insert(std::make_pair(entity->_id, entity));
    entity->EnableAll();
}

const std::map<int, Entity *> &EntityManager::GetAllEntities() const
{
    return _entity_map;
}

int EntityManager::GetNumberOfEntities()
{
    return _entity_map.size();
}

bool EntityManager::HasEntity(int id)
{
    return !IDAvailable(id);
}

LuaList<Entity *> *EntityManager::AsLuaList()
{
    return LuaList<Entity *>::FromMapToLuaList<int, Entity *>(_entity_map);
}

bool EntityManager::IDAvailable(int id)
{
    return _entity_map.find(id) == _entity_map.end();
}

void EntityManager::Clear()
{
    _entity_map.clear();
}

void EntityManager::OnEvent(Event &e)
{
    if (e.id == EventType::SPAWN_ENTITY_EVENT_PROTOTYPE)
    {
        Entity *entity = LuaEntityFactory::Instance()->GetEntity(e.sender_id);
        RegisterEntity(entity);

        Event event(EventType::ENTITY_SPAWNED_EVENT, -1, e.target_id, entity);
        DispatchMessage(event);
    }
    else if (e.id == EventType::SPAWN_ENTITY_EVENT)
    {
        Entity *entity = e.InfoToType<Entity *>();
        RegisterEntity(entity);
        Event event(EventType::ENTITY_SPAWNED_EVENT, -1, e.target_id, entity);
        DispatchMessage(event);
    }
    else if (e.id == EventType::DELETE_ENTITY_EVENT)
    {
        if (HasEntity(e.target_id))
        {
            MarkForDelete(GetEntityByID(e.target_id));
        }
    }
}

std::list<Subscription> EntityManager::GetSubscriptions()
{
    std::list<Subscription> subs =
        {
            Subscription(EventType::SPAWN_ENTITY_EVENT_PROTOTYPE),
            Subscription(EventType::DELETE_ENTITY_EVENT),
            Subscription(EventType::SPAWN_ENTITY_EVENT)};

    return subs;
}

void EntityManager::MarkForDelete(Entity *e)
{
    _delete_set.insert(e);
}

void EntityManager::Clean()
{
    for (auto it = _delete_set.begin(); it != _delete_set.end();)
    {
        Entity *e = *it;
        DeregisterEntity(e->ID());
        delete e;
        it = _delete_set.erase(it);
    }
}

EntityManager::~EntityManager()
{
    std::cout << "Cleaning up entities...." << std::endl;
    for (auto it = _entity_map.begin(); it != _entity_map.end();)
    {
        Entity *to_delete = it->second;
        it = _entity_map.erase(it);
        delete to_delete;
    }
}

Entity *EntityManager::GetNewest()
{
    if (_entity_map.empty())
        return nullptr;
    else
        return _entity_map.rbegin()->second;
}

int EntityManager::Size()
{
    return _entity_map.size();
}