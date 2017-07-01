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

    return lua_list; //TODO: Fix Leak
}

std::list<ComponentUser*>* ComponentUserBase::GetAllUsersWithComponents(std::list<std::string> list)
{
    std::list<ComponentUser*>* matches = new std::list<ComponentUser*>();
    auto comp_name = list.begin();

    if(!ComponentExists(*comp_name))
    {
        //invalid component name 
        return nullptr;
    }

    matches->merge(*GetAllUsersWithComponent(*comp_name));
    comp_name++;

    while(comp_name != list.end())
    {
        for(auto user_it = matches->begin(); user_it != matches->end(); user_it++)
        {
            if(!(*user_it)->HasComponent(*comp_name))
            {
                matches->erase(user_it);
            }
        }
    }

    return matches;
}

std::list<ComponentUser*>* ComponentUserBase::GetAllUsersWithComponents(std::initializer_list<std::string> list)
{
    std::list<std::string> linked_list;

    for(auto it = list.begin(); it != list.end(); it++)
    {
        linked_list.push_back(*it);
    }

    return GetAllUsersWithComponents(linked_list);
}

LuaList<ComponentUser*> ComponentUserBase::GetAllUsersWithComponentsAsLuaList(LuaRef& list)
{
    std::list<std::string> comp_list;
    
    LuaUniversal::ListFromTable<std::string>(list,comp_list);

    std::list<ComponentUser*>* matches = GetAllUsersWithComponents(comp_list);
    LuaList<ComponentUser*> lua_list;

    LuaList<ComponentUser*>::FromListToLuaList(*matches, lua_list);

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
    return lua_list; //TODO: Fix Leak
}