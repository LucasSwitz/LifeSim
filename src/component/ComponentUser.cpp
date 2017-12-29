#include "ComponentUser.h"
#include "src/component/ComponentUserBase.h"

int ComponentUser::last_id = -1;
typedef std::unordered_map<std::string, ptr<Component>> component_map;

int ComponentUser::ID() const
{
    return _id;
}

int ComponentUser::Type() const
{
    return _type;
}

void ComponentUser::SetID(int id)
{
    _id = id;
}

void ComponentUser::RemoveComponent(std::string name)
{
    DisableComponent(name);

    if (HasComponent(name))
        _components.erase(_components.find(name));
}

void ComponentUser::EnableComponent(std::string name)
{
    if (HasComponent(name) && _listener)
        _listener->OnEnableComponent(this, name);
}

void ComponentUser::EnableAll()
{
    if (_listener)
    {
        for (auto it = _components.begin(); it != _components.end(); it++)
        {
            _listener->OnEnableComponent(this, it->first);
        }
    }
    else
    {
        std::cout << "No Listener" << std::endl;
    }
}

void ComponentUser::DisableAll()
{
    if (_listener)
    {
        for (auto it = _components.begin(); it != _components.end(); it++)
        {
            _listener->OnDisableComponent(this, it->first);
        }
    }
}

void ComponentUser::DisableComponent(std::string name)
{
    if (HasComponent(name) && _listener)
        _listener->OnDisableComponent(this, name);
}

bool ComponentUser::HasComponent(std::string name) const
{
    return _components.find(name) != _components.end();
}

void ComponentUser::AddComponent(ptr<Component> component)
{
    std::string component_name = component->GetName();

    _components.insert(std::make_pair(component_name, component));
}

std::string ComponentUser::GetComponentValueString(std::string component_name, std::string value_name) const
{
    if (!HasComponent(component_name))
    {
        //std::cout << "has no component: " << component_name << std::endl;
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
        //std::cout << "has no component: " << component_name << std::endl;
        return 0;
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

bool ComponentUser::GetComponentValueBool(std::string component_name, std::string component_name_value)
{
    if (!HasComponent(component_name))
    {
        std::cout << "has no component: " << component_name << std::endl;
        return false;
    }
    return _components.at(component_name)->GetBoolValue(component_name_value);
}

void ComponentUser::SetComponentValueBool(std::string component_name, std::string component_name_value, bool value)
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

ptr<Component> ComponentUser::GetComponent(std::string name)
{
    return _components.at(name);
}

Component *ComponentUser::GetComponentUnshared(std::string name)
{
    return (GetComponent(name)).get();
}

component_map &ComponentUser::GetAllComponents()
{
    return _components;
}

void ComponentUser::AddComponentValue(const std::string &component_name, const std::string &value_name, const std::string& value)
{
    if (!HasComponent(component_name))
    {
        AddComponent(std::make_shared<Component>(component_name));
    }

    GetComponent(component_name)->SetStringValue(value_name, value);
}

void ComponentUser::AddComponentValue(const std::string &component_name, const std::string &value_name, bool value)
{
    if (!HasComponent(component_name))
    {
        AddComponent(std::make_shared<Component>(component_name));
    }

    GetComponent(component_name)->SetBoolValue(value_name, value);
}

void ComponentUser::AddComponentValue(const std::string &component_name, const std::string &value_name, float value)
{
    if (!HasComponent(component_name))
    {
        AddComponent(std::make_shared<Component>(component_name));
    }

    GetComponent(component_name)->SetFloatValue(value_name, value);
}

void ComponentUser::SetListener(ComponentUserListener *listener)
{
    _listener = listener;
}

using json = nlohmann::json;
ptr<ComponentUser> ComponentUser::FromJson(int type, const json &json_cu)
{
    ptr<ComponentUser> user = std::make_shared<ComponentUser>(type);
    FromJson(user, json_cu);
    return user;
}

void ComponentUser::FromJson(ptr<ComponentUser> user, const json &json_cu)
{
    auto components = json_cu["components"];

    for (auto it = components.begin(); it != components.end(); it++)
    {
        json component = *it;
        user->AddComponent(Component::FromJson(component, it.key()));
    }
}

ComponentUser::~ComponentUser()
{
    /*for (auto it = _components.begin(); it != _components.end();)
    {
        if (ComponentUserBase::Instance())
        {
            ComponentUserBase::Instance()->DeRegister(it->first, *this);
        }

        Component *to_delete = it->second;
        it = _components.erase(it);

        delete to_delete;
    }*/
}
