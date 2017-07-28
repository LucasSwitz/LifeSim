#include "ComponentUser.h"
#include "src/component/ComponentUserBase.h"

void ComponentUser::RemoveComponent(std::string name)
{
    if (HasComponent(name))
        _components.erase(_components.find(name));
    ComponentUserBase::Instance()->DeRegister(name, *this);
}

void ComponentUser::EnableComponent(std::string name)
{
    if (HasComponent(name))
        ComponentUserBase::Instance()->Register(name, *this);
}

void ComponentUser::EnableAll()
{
    for (auto it = _components.begin(); it != _components.end(); it++)
    {
        ComponentUserBase::Instance()->Register(it->first, *this);
    }
}

void ComponentUser::DisableAll()
{
    for (auto it = _components.begin(); it != _components.end(); it++)
    {
        ComponentUserBase::Instance()->DeRegister(it->first, *this);
    }
}

void ComponentUser::DisableComponent(std::string name)
{
    if (HasComponent(name))
        ComponentUserBase::Instance()->DeRegister(name, *this);
}

bool ComponentUser::HasComponent(std::string name) const
{
    return _components.find(name) != _components.end();
}

void ComponentUser::AddComponent(Component *component, bool add_to_user_base)
{
    std::string component_name = component->GetName();

    _components.insert(std::make_pair(component_name, component));
    if (add_to_user_base)
        EnableComponent(component_name);
}

std::string ComponentUser::GetComponentValueString(std::string component_name, std::string value_name) const
{
    if (!HasComponent(component_name))
    {
        std::cout << "has no component: " << component_name << std::endl;
        return "";
    }
    else if (!_components.at(component_name)->HasStringValue(value_name))
    {
        std::cout << "has no value: " << value_name << std::endl;
    }
    return _components.at(component_name)->GetStringValue(value_name);
}

void ComponentUser::SetComponentValueString(std::string component_name, std::string component_name_value, std::string value)
{
    _components.at(component_name)->SetStringValue(component_name_value, value);
}

float ComponentUser::GetComponentValueFloat(std::string component_name, std::string value_name) const
{
    if (!HasComponent(component_name))
    {
        std::cout << "has no component: " << component_name << std::endl;
        return -1;
    }
    return _components.at(component_name)->GetFloatValue(value_name);
}

void ComponentUser::SetComponentValueFloat(std::string component_name, std::string component_name_value, float value)
{
    if (HasComponent(component_name))
    {
        _components.at(component_name)->SetFloatValue(component_name_value, value);
    }
    else
    {
        std::cout << "has no component: " << component_name << std::endl;
    }
}

bool ComponentUser::GetComponentBoolValue(std::string component_name, std::string component_name_value)
{
    if (!HasComponent(component_name))
    {
        std::cout << "has no component: " << component_name << std::endl;
        return false;
    }
    return _components.at(component_name)->GetBoolValue(component_name_value);
}

void ComponentUser::SetComponentBoolValue(std::string component_name, std::string component_name_value, bool value)
{
    if (!HasComponent(component_name))
    {
        std::cout << "has no component: " << component_name << std::endl;
    }
    _components.at(component_name)->SetBoolValue(component_name_value, value);
}

void ComponentUser::CallFunction(std::string component_name, std::string function_name)
{
    _components.at(component_name)->GetFunctionValue(function_name);
}

Component *ComponentUser::GetComponent(std::string name)
{
    return _components.at(name);
}

std::unordered_map<std::string, Component *> &ComponentUser::GetAllComponents()
{
    return _components;
}


void ComponentUser::AddComponentValue(const std::string &component_name, const std::string &value_name, std::string value)
{
    if (!HasComponent(component_name))
    {
        AddComponent(new Component(component_name));
    }

    GetComponent(component_name)->SetStringValue(value_name,value);
}

void ComponentUser::AddComponentValue(const std::string &component_name, const std::string &value_name, bool value)
{
    if (!HasComponent(component_name))
    {
        AddComponent(new Component(component_name));
    }

    GetComponent(component_name)->SetBoolValue(value_name,value);
}

void ComponentUser::AddComponentValue(const std::string &component_name, const std::string &value_name, float value)
{
    if (!HasComponent(component_name))
    {
        AddComponent(new Component(component_name));
    }

    GetComponent(component_name)->SetFloatValue(value_name, value);
}


ComponentUser::~ComponentUser()
{
    for (auto it = _components.begin(); it != _components.end();)
    {
        if(ComponentUserBase::Instance())
            ComponentUserBase::Instance()->DeRegister(it->first, *this);
        
        Component* to_delete = it->second;
        it = _components.erase(it);

        delete to_delete;
    }
}