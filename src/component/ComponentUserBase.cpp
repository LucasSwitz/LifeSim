#include "ComponentUserBase.h"
#include "src/component/ComponentUser.h"


void ComponentUserBase::Register(std::string component_name,ComponentUser& user)
{

    if(!ComponentExists(component_name))
    {
        _component_users_directory.insert(std::make_pair(component_name, new std::list<ComponentUser*>()));
    }

    std::list<ComponentUser*>* list = _component_users_directory.at(component_name);
    list->push_back(&user);

}

void ComponentUserBase::DeRegister(std::string component_name,ComponentUser& user)
{
    if(!ComponentExists(component_name))
        return;

    std::list<ComponentUser*>* list = GetAllUsersWithComponent(component_name);

    for(auto it = list->begin(); it != list->end(); it++)
    {
        if (*it == &user)
            list->erase(it);
    }
}

bool ComponentUserBase::ComponentExists(std::string component_name)
{
    return _component_users_directory.find(component_name) != _component_users_directory.end();
}

LuaList<Entity*>* ComponentUserBase::GetAllEntitesWithComponentAsLuaList(std::string component_name)
{
    std::list<ComponentUser*>* list = GetAllUsersWithComponent(component_name);
    std::list<Entity*> entities;

    for(auto it = list->begin(); it != list->end(); it++)
    {
        ComponentUser* user = *it;
        Entity* e = dynamic_cast<Entity*>(user);
        if(e)
            entities.push_back(e);
    }

    LuaList<Entity*>* lua_list = new LuaList<Entity*>();
    LuaList<Entity*>::FromListToLuaList<Entity*>(entities, *lua_list);

    return lua_list;
}

std::list<ComponentUser*>* ComponentUserBase::GetAllUsersWithComponent(std::string component_name)
{
    if(!ComponentExists(component_name))
        return new std::list<ComponentUser*>();
    else
        return _component_users_directory.at(component_name);
}

LuaList<ComponentUser*>* ComponentUserBase::GetAllUsersWithComponentAsLuaList(std::string component_name)
{
    std::list<ComponentUser*>* list = GetAllUsersWithComponent(component_name);
    LuaList<ComponentUser*>* lua_list = new LuaList<ComponentUser*>();
    LuaList<ComponentUser*>::FromListToLuaList<ComponentUser*>(*list, *lua_list);
    return lua_list;
}