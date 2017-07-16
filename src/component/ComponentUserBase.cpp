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

void ComponentUserBase::DeRegister(std::string component_name, ComponentUser& user)
{
    if(!ComponentExists(component_name))
        return;

    std::list<ComponentUser*> list = GetAllUsersWithComponent(component_name);

    for(auto it = list.begin(); it != list.end(); it++)
    {
        if (*it == &user)
            it = list.erase(it);
    }
}

bool ComponentUserBase::ComponentExists(std::string component_name)
{
    return _component_users_directory.find(component_name) != _component_users_directory.end();
}

LuaList<Entity*> ComponentUserBase::GetAllEntitesWithComponentAsLuaList(std::string component_name)
{
    std::list<ComponentUser*> list = GetAllUsersWithComponent(component_name);
    std::list<Entity*> entities;

    for(auto it = list.begin(); it != list.end(); it++)
    {
        ComponentUser* user = *it;
        Entity* e = dynamic_cast<Entity*>(user);
        if(e)
            entities.push_back(e);
    }

    LuaList<Entity*> lua_list;
    LuaList<Entity*>::FromListToLuaList<Entity*>(entities, lua_list);

    return lua_list;
}

std::list<ComponentUser*> ComponentUserBase::GetAllUsersWithComponents(std::list<std::string> list)
{
    std::list<ComponentUser*> matches;
    std::list<std::string>::iterator comp_name = list.begin();
    
    if(!ComponentExists(*comp_name) || list.empty())
    {
        //invalid component name 
        return matches;
    }

    matches.merge(GetAllUsersWithComponent(*comp_name));
    comp_name = std::next(comp_name);
    while(matches.size() != 0 && comp_name != list.end())
    {
        for(auto user_it = matches.begin(); user_it != matches.end();)
        {
            if(!((*user_it)->HasComponent(*comp_name)))
            {
                user_it = matches.erase(user_it);
            }
            else
                user_it++;
        }
         comp_name = std::next(comp_name);
    }
    return matches;
}

std::list<ComponentUser*> ComponentUserBase::GetAllUsersWithComponents(std::initializer_list<std::string> list)
{
    std::list<std::string> linked_list;

    for(auto it = list.begin(); it != list.end(); it++)
    {
        linked_list.push_back(*it);
    }

    return GetAllUsersWithComponents(linked_list);
}

LuaList<ComponentUser*> ComponentUserBase::GetAllUsersWithComponentsAsLuaList(lua_State* L)
{
    std::list<std::string> comp_list; 
    LuaUniversal::StringListFromLuaTable(L, comp_list);
    std::list<ComponentUser*> matches = GetAllUsersWithComponents(comp_list);
    LuaList<ComponentUser*> lua_list;
    LuaList<ComponentUser*>::FromListToLuaList(matches, lua_list);

    return lua_list;
}

std::list<ComponentUser*> ComponentUserBase::GetAllUsersWithComponent(std::string component_name)
{
    std::list<ComponentUser*> matches;
    if(ComponentExists(component_name))
        matches = *_component_users_directory.at(component_name);
    return matches;
}

LuaList<ComponentUser*> ComponentUserBase::GetAllUsersWithComponentAsLuaList(std::string component_name)
{
    std::list<ComponentUser*> list = GetAllUsersWithComponent(component_name);
    LuaList<ComponentUser*> lua_list;
    LuaList<ComponentUser*>::FromListToLuaList<ComponentUser*>(list, lua_list);
    return lua_list;
}