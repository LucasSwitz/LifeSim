#include "ComponentUser.h"
#include "src/component/ComponentUserBase.h"

void ComponentUser::RemoveComponent(std::string name)
{
    if(HasComponent(name))
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

Component *ComponentUser::GetComponent(std::string name)
{
    return _components.at(name);
}