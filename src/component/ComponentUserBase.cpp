#include "ComponentUserBase.h"
#include "src/component/ComponentUser.h"

ComponentUserBase* ComponentUserBase::_instance = nullptr;

void ComponentUserBase::Register(std::string component_name,ComponentUser& user)
{
    if(!ComponentExists(component_name))
    {
        _component_users_directory.insert(std::make_pair(component_name, new std::list<ComponentUser*>()));
    }

    std::list<ComponentUser*>* list = _component_users_directory.at(component_name);
    list->push_back(&user);

    UpdateSubscribers(ComponentUserBaseEvent::ADD,component_name,&user);
}

void ComponentUserBase::DeRegister(std::string component_name, ComponentUser& user)
{
    if(!ComponentExists(component_name))
        return;

    std::list<ComponentUser*>* list = GetAllUsersWithComponent(component_name);

    for(auto it = list->begin(); it != list->end();)
    {
        if (*it == &user)
            it = list->erase(it);
        else
            it++;
    }

    UpdateSubscribers(ComponentUserBaseEvent::REMOVE,component_name,&user);
}

bool ComponentUserBase::ComponentExists(std::string component_name)
{
    return _component_users_directory.find(component_name) != _component_users_directory.end();
}

void ComponentUserBase::GetAllEntitesWithComponentAsLuaList(LuaList<Entity*>* lua_list, std::string component_name)
{
    std::list<ComponentUser*>* list = GetAllUsersWithComponent(component_name);
    std::list<Entity*> entities;

    if(!list)
        return;

    for(auto it = list->begin(); it != list->end(); it++)
    {
        ComponentUser* user = *it;
        Entity* e = dynamic_cast<Entity*>(user);
        if(e)
            lua_list->Add(e);
    }
}

void ComponentUserBase::GetAllUsersWithComponents(std::initializer_list<std::string> list,
                                    std::list<ComponentUser*>& user_list)
{
    std::list<std::string> comp_list;
    for(auto it = list.begin(); it != list.end(); it++)
    {
        comp_list.push_back(*it);
    }

    GetAllUsersWithComponents(comp_list, user_list);
}


void ComponentUserBase::GetAllUsersWithComponents(std::list<std::string>& list, std::list<ComponentUser*>& matches)
{
    std::list<std::string>::iterator comp_name = list.begin();
    
    if(!ComponentExists(*comp_name) || list.empty())
    {
        return;
    }

    std::list<ComponentUser*>* first_matches = GetAllUsersWithComponent(*comp_name);

    for(ComponentUser* user : *first_matches)
    {
        matches.push_back(user);
    }

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
}

std::list<ComponentUser*>* ComponentUserBase::GetAllUsersWithComponent(std::string component_name)
{
    if(ComponentExists(component_name))
    {   
        return _component_users_directory.at(component_name);
    }
    else
        return nullptr;
}

void ComponentUserBase::GetAllUsersWithComponentsAsLuaList(LuaList<ComponentUser*>* lua_list, lua_State* L)
{
    std::list<std::string> comp_list; 
    LuaUniversal::StringListFromLuaTable(L, comp_list);

    std::list<ComponentUser*> matches;
    GetAllUsersWithComponents(comp_list, matches);
    LuaList<ComponentUser*>::FromListToLuaList(matches, *lua_list);
}


void ComponentUserBase::GetAllUsersWithComponentAsLuaList(std::string& component_name, LuaList<ComponentUser*>& lua_list)
{
    std::list<ComponentUser*>* list = GetAllUsersWithComponent(component_name);
    LuaList<ComponentUser*>::FromListToLuaList<ComponentUser*>(*list, lua_list);
}

void ComponentUserBase::AddSubscriber(ComponentUserBaseSubscriber* subscriber, std::string component_name)
{
    if(_subscribers.find(component_name) == _subscribers.end())
        _subscribers.emplace(component_name, new std::list<ComponentUserBaseSubscriber*>());
    _subscribers.at(component_name)->push_back(subscriber);
}

void ComponentUserBase::UpdateSubscribers(ComponentUserBaseEvent::Type _type, std::string component_name,
        ComponentUser* user)
{
    if(_subscribers.find(component_name) == _subscribers.end())
        return;

    auto subs = _subscribers.at(component_name);

    ComponentUserBaseEvent e(_type,user,component_name);

    for(auto it = subs->begin(); it != subs->end(); it++)
    {
        (*it)->OnEvent(e);
    }
}