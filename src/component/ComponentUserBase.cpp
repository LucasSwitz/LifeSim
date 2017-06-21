#include "ComponentUserBase.h"


void ComponentUserBase::Register(std::string component_name, ComponentUser& component_user)
{
    std::list<ComponentUser>* list = nullptr;

    if(!ComponentExists(component_name))
    {
        list = new std::list<ComponentUser>();
        list->push_back(component_user);
        _component_users_directory.insert(component_name, user);
    }
    else
    {
        list = _component_users_directory.at(component_name);
        list->push_back(component_user);
    }
}

void ComponentUserBase::DeRegister(std::string component_name,ComponentUser& user)
{
    if(!ComponentExists(component_name))
        return;

    std::list<ComponentUser*> list = _component_users_directory.at(component_name);

    for(auto it = list.being(); it != list.end(); it++)
    {
        if (**it == user)
            list.erase(it);
    }


}

bool ComponentUserBase::ComponentExists(std::string component_name)
{
    return _component_users_directory.find(component_name) != _component_users_directory.end();
}

std::list<ComponentUser>* ComponentUserBase::GetAllUsersWithComponent(std::string component_name)
{
    if(!ComponentExists(component_name))
        return new std::list<ComponentUser*>();
    else
        return _component_users_directory.at(component_name);
}