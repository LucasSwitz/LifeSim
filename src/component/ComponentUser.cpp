#include "ComponentUser.h"
#include "src/component/ComponentUserBase.h"

void ComponentUser::RemoveComponent(std::string name)
{
    if (HasComponent(name))
        _components.erase(_components.find(name));
    ComponentUserBase::Instance()->DeRegister(name, *this);
}

bool ComponentUser::HasComponent(std::string name)
{
    return _components.find(name) != _components.end();
}

void ComponentUser::AddComponent(Component *component)
{
    std::string component_name = component->GetName();
    _components.insert(std::make_pair(component_name, component));

    ComponentUserBase::Instance()->Register(component_name, *this);
}

std::string ComponentUser::GetComponentValueString(std::string component_name, std::string value_name)
{
    if (!HasComponent(component_name))
    {
        std::cout << "has no component: " << component_name << std::endl;
        return "";
    }
    return _components.at(component_name)->GetStringValue(value_name);
}

std::string ComponentUser::SetComponentValueString(std::string component_name, std::string component_name_value, std::string value)
{
    _components.at(component_name)->SetStringValue(component_name_value, value);
}

float ComponentUser::GetComponentValueFloat(std::string component_name, std::string value_name)
{
    if (!HasComponent(component_name))
    {
        std::cout << "has no component: " << component_name << std::endl;
        return -1;
    }
    return _components.at(component_name)->GetFloatValue(value_name);
}

float ComponentUser::SetComponentValueFloat(std::string component_name, std::string component_name_value, float value)
{
    _components.at(component_name)->SetFloatValue(component_name_value, value);
}

void *ComponentUser::GetComponetValueFuntion(std::string component_name, std::string component_name_value)
{
    if (!HasComponent(component_name))
    {
        std::cout << "has no component: " << component_name << std::endl;
        return nullptr;
    }
    return _components.at(component_name)->GetFunctionValue(component_name_value);
}

Component *ComponentUser::GetComponent(std::string name)
{
    return _components.at(name);
}
