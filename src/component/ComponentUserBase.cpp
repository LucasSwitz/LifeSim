#include "ComponentUserBase.h"
#include "src/component/ComponentUser.h"
typedef std::unordered_map<std::string, ptr<std::list<ptr<ComponentUser>>>> component_user_directoy;

typedef std::unordered_map<std::string, ptr<std::list<ComponentUserBaseSubscriber *>>>
    component_user_subscriber_directory;

typedef ptr<std::list<ptr<ComponentUser>>> component_user_list_ptr;

typedef std::list<ComponentUserBaseSubscriber *> component_user_subscriber_list;

typedef std::list<ptr<ComponentUser>> cu_list;

void ComponentUserBase::Register(std::string component_name, ComponentUser &user)
{
     ptr<ComponentUser> user_ptr = nullptr;

    if (!ComponentExists(component_name))
        _component_users_directory.insert(std::make_pair(component_name, std::make_shared<cu_list>()));

    if (!HasComponentUser(user.ID())){
        user_ptr = ptr<ComponentUser>(&user);
        AddComponentUser(ptr<ComponentUser>(&user));
    }
    else{
        user_ptr = GetComponentUser(user.ID());
    } 

    auto list = _component_users_directory.at(component_name);
    list->push_back(user_ptr);

    _registration_count.find(user.ID())->second += 1;

    UpdateSubscribers(ComponentUserBaseEvent::ADD, component_name, user_ptr);
}

void ComponentUserBase::DeRegister(std::string component_name, ComponentUser &user)
{
    if (!ComponentExists(component_name))
        return;

    auto list = GetAllUsersWithComponentMutable(component_name);

    for (auto it = list->begin(); it != list->end();)
    {
        if (it->get() == &user)
        {
            it = list->erase(it);
            _registration_count.find(user.ID())->second -= 1;
        }
        else
            it++;
    }

    UpdateSubscribers(ComponentUserBaseEvent::REMOVE, component_name, ptr<ComponentUser>(&user));

    if (GetRegistrationCount(user.ID()) == 0)
        RemoveComponentUser(ptr<ComponentUser>(&user));
}

bool ComponentUserBase::ComponentExists(std::string component_name) const
{
    return _component_users_directory.find(component_name) != _component_users_directory.end();
}

void ComponentUserBase::GetAllEntitesWithComponentAsLuaList(LuaList<Entity *> *lua_list, std::string component_name)
{
    const component_user_list_ptr list = GetAllUsersWithComponent(component_name);
    std::list<Entity *> entities;

    if (!list)
        return;

    for (auto it = list->begin(); it != list->end(); it++)
    {
        ptr<ComponentUser> user = *it;
        Entity *e = dynamic_cast<Entity *>(user.get());
        if (e)
            lua_list->Add(e);
    }
}

void ComponentUserBase::GetAllUsersWithComponents(std::initializer_list<std::string> list,
                                                  std::list<ptr<ComponentUser>> &user_list)
{
    std::list<std::string> comp_list;

    for (auto it = list.begin(); it != list.end(); it++)
    {
        comp_list.push_back(*it);
    }

    GetAllUsersWithComponents(comp_list, user_list);
}

void ComponentUserBase::GetAllUsersWithComponents(std::list<std::string> &list, std::list<ptr<ComponentUser>> &matches)
{
    std::list<std::string>::iterator comp_name = list.begin();

    if (!ComponentExists(*comp_name) || list.empty())
    {
        std::cout << "No user with component: " << *comp_name << std::endl;
        return;
    }

    auto first_matches = GetAllUsersWithComponent(*comp_name);

    for (ptr<ComponentUser> user : *first_matches)
    {
        matches.push_back(user);
    }

    comp_name = std::next(comp_name);

    while (matches.size() != 0 && comp_name != list.end())
    {
        for (auto user_it = matches.begin(); user_it != matches.end();)
        {
            if (!((*user_it)->HasComponent(*comp_name)))
            {
                user_it = matches.erase(user_it);
            }
            else
                user_it++;
        }
        comp_name = std::next(comp_name);
    }
}

const component_user_list_ptr ComponentUserBase::
    GetAllUsersWithComponent(std::string component_name) const
{
    if (ComponentExists(component_name))
    {
        return _component_users_directory.at(component_name);
    }
    else
        return nullptr;
}

component_user_list_ptr ComponentUserBase::
    GetAllUsersWithComponentMutable(std::string component_name)
{
    if (ComponentExists(component_name))
    {
        return _component_users_directory.at(component_name);
    }
    else
        return nullptr;
}

void ComponentUserBase::GetAllUsersWithComponentsAsLuaList(LuaList<ComponentUser *> *lua_list, lua_State *L)
{
    std::list<std::string> comp_list;
    LuaUniversal::StringListFromLuaTable(L, comp_list);

    std::list<ptr<ComponentUser>> matches;
    GetAllUsersWithComponents(comp_list, matches);

    std::list<ComponentUser *> raw_lst;
    expose_ptrs(matches, raw_lst);

    LuaList<ComponentUser *>::FromListToLuaList(raw_lst, *lua_list);
}

void ComponentUserBase::GetAllUsersWithComponentAsLuaList(std::string &component_name, LuaList<ComponentUser *> &lua_list)
{
    const component_user_list_ptr list = GetAllUsersWithComponent(component_name);

    std::list<ComponentUser *> raw_lst;
    expose_ptrs(*list, raw_lst);
    LuaList<ComponentUser *>::FromListToLuaList<ComponentUser *>(raw_lst, lua_list);
}

void ComponentUserBase::AddSubscriber(ComponentUserBaseSubscriber *subscriber, std::string component_name)
{
    if (_subscribers.find(component_name) == _subscribers.end())
        _subscribers.insert(std::make_pair(component_name,
                                           ptr<component_user_subscriber_list>(new component_user_subscriber_list)));
    _subscribers.at(component_name)->push_back(subscriber);
}

void ComponentUserBase::UpdateSubscribers(ComponentUserBaseEvent::Type _type, std::string component_name,
                                          ptr<ComponentUser> user)
{
    if (_subscribers.find(component_name) == _subscribers.end())
        return;

    auto subs = _subscribers.at(component_name);

    ComponentUserBaseEvent e(_type, user.get(), component_name);

    for (auto it = subs->begin(); it != subs->end(); it++)
    {
        (*it)->OnEvent(e);
    }
}

ptr<ComponentUser> ComponentUserBase::GetComponentUser(int id)
{
    if (HasComponentUser(id))
        return _all_users.at(id);
    return nullptr;
}

void ComponentUserBase::AddComponentUser(ptr<ComponentUser> user)
{
    _all_users.insert(std::make_pair(user->ID(), user));
    _registration_count.insert(std::make_pair(user->ID(), 0));
    user->SetListener(this);
}

void ComponentUserBase::RemoveComponentUser(ptr<ComponentUser> user)
{
    _all_users.erase(_all_users.find(user->ID()));
    _registration_count.erase(_registration_count.find(user->ID()));
}

bool ComponentUserBase::HasComponentUser(int id)
{
    return _all_users.find(id) != _all_users.end();
}

int ComponentUserBase::GetRegistrationCount(int id)
{
    if (IsRegistered(id))
        return _registration_count.at(id);
    return 0;
}

bool ComponentUserBase::IsRegistered(int id)
{
    return _registration_count.find(id) != _registration_count.end();
}

void ComponentUserBase::OnEnableComponent(ComponentUser* user, const std::string component_name)
{
    Register(component_name, *user);
}

void ComponentUserBase::OnDisableComponent(ComponentUser* user, const std::string component_name)
{
    DeRegister(component_name, *user);
}
