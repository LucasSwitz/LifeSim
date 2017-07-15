#ifndef COMPONENT_H
#define COMPONENT_H

/**
    Class the Controls all component logic. This class can be extended to support other forms of component
    loading (from Lua objects for example).
**/

#include <unordered_map>
#include <iostream>

class Component
{

  public:
    template <typename T>
    struct ComponentValue
    {
        ComponentValue(std::string name_, T value_) : name(name_), value(value_)
        {

        }

        void SetValue(T new_value)
        {
            value = new_value;
        }

        T GetValue() 
        {
            return value;
        }

        std::string GetName() 
        {
            return name;
        }

        std::string name;
        T value;
    };

    void SetStringValue(std::string name, std::string value)
    {
        _string_components.at(name).SetValue(value);
    }

    void SetFloatValue(std::string name, float value)
    {
        _float_components.at(name).SetValue(value);
    }

    float GetFloatValue(std::string name) 
    {
        if(!HasFloatValue(name))
        {
            std::cout << "Component [" << GetName() << "] does not have value: " << name << std::endl;
            return -1;
        }
        return _float_components.at(name).GetValue();
    }

    bool HasFloatValue(std::string name) const
    {
        return _float_components.find(name) != _float_components.end();
    }

    std::string GetStringValue(std::string name)
    {
        if(!HasStringValue(name))
        {
            std::cout << "Component [" << GetName() << "] does not have value: " << name << std::endl;
            return "";
        }
        return _string_components.at(name).GetValue();
    }

    bool HasStringValue(std::string name) const
    {
        return _string_components.find(name) != _string_components.end();
    }

    void* GetFunctionValue(std::string name)
    {
        return _functional_components.at(name).GetValue();
    }

    std::string GetName() const
    {
        return _name;
    }

    Component* GetSubcomponent(std::string name)
    {
        return _sub_components.at(name);
    }

    bool GetBoolValue(std::string name)
    {
        if(!HasBoolValue(name))
        {
            std::cout << "Component [" << GetName() << "] does not have value: " << name << std::endl;
            return false;
        }
        return _bool_components.at(name).GetValue();
    }

    void SetBoolValue(std::string name, bool value)
    {
        if(HasBoolValue(name))
        {
            _bool_components.at(name).SetValue(value);
        }
    }

    bool HasBoolValue(std::string name)
    {
        return _bool_components.find(name) != _bool_components.end();
    }

    std::unordered_map<std::string, ComponentValue<std::string>>& GetAllStringValues()
    {
        return _string_components;
    }

    std::unordered_map<std::string, ComponentValue<float>>& GetAllFloatValues()
    {
        return _float_components;
    }

    std::unordered_map<std::string, ComponentValue<bool>>& GetAllBoolValues()
    {
        return _bool_components;
    }

  protected:
    void AddValue(std::string name, std::string value)
    {
        _string_components.insert(std::make_pair(name, ComponentValue<std::string>(name,value)));
    }

    void AddValue(std::string name, float value)
    {
        _float_components.insert(std::make_pair(name, ComponentValue<float>(name,value)));
    }

    void AddValue(std::string name, bool value)
    {
        _bool_components.insert(std::make_pair(name, ComponentValue<bool>(name,value)));
    }

    void AddSubcomponent(Component* sub_component)
    {
        _sub_components.insert(std::make_pair(sub_component->_name, sub_component));
    }

    Component(std::string name="") : _name(name){};

  protected:
    std::string _name;
  private:
    std::unordered_map<std::string, ComponentValue<std::string>> _string_components;
    std::unordered_map<std::string, ComponentValue<float>> _float_components;
    std::unordered_map<std::string, ComponentValue<void*>> _functional_components;
    std::unordered_map<std::string, ComponentValue<bool>> _bool_components;
    std::unordered_map<std::string, Component*> _sub_components;
};

#endif