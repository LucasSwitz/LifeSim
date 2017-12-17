#ifndef COMPONENT_H
#define COMPONENT_H

/**
    Class the Controls all component logic. This class can be extended to support other forms of component
    loading (from Lua objects for example). ComponentUsers can be indenfified by their id field. This id
    should be consitent across all child classes that require unique identification (i.e Entity).
**/
#include "src/utils/Globals.h"
#include <unordered_map>
#include <iostream>

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

    T *GetValuePtr()
    {
        return &value;
    }

    std::string GetName()
    {
        return name;
    }

    std::string name;
    T value;
};

class Component
{
  public:
    template <typename T>
    using component_value_map =
        std::unordered_map<std::string, ComponentValue<T>>;

    template <typename T>
    using subcomponent_map =
        std::unordered_map<std::string, ptr<Component>>;

    Component(std::string name = "") : _name(name){};

    //STRING ----------------------------

    bool HasStringValue(std::string name) const
    {
        return _string_components.find(name) != _string_components.end();
    }

    void SetStringValue(std::string name, std::string value)
    {
        if (HasStringValue(name))
            _string_components.at(name).SetValue(value);
        else
            AddValue(name, value);
    }

    std::string GetStringValue(std::string name)
    {
        if (!HasStringValue(name))
        {
            return "";
        }
        return _string_components.at(name).GetValue();
    }

    component_value_map<std::string> &GetAllStringValues()
    {
        return _string_components;
    }

    //FLOATS ----------------------------------------
    bool HasFloatValue(std::string name) const
    {
        return _float_components.find(name) != _float_components.end();
    }

    void SetFloatValue(std::string name, float value)
    {
        if (HasFloatValue(name))
            _float_components.at(name).SetValue(value);
        else
            AddValue(name, value);
    }

    float GetFloatValue(std::string name)
    {
        if (!HasFloatValue(name))
        {
            return -1;
        }
        return _float_components.at(name).GetValue();
    }

    component_value_map<float> &GetAllFloatValues()
    {
        return _float_components;
    }

    //BOOLS ---------------------
    bool HasBoolValue(std::string name)
    {
        return _bool_components.find(name) != _bool_components.end();
    }

    bool GetBoolValue(std::string name)
    {
        if (!HasBoolValue(name))
        {
            return false;
        }
        return _bool_components.at(name).GetValue();
    }

    void SetBoolValue(std::string name, bool value)
    {
        if (HasBoolValue(name))
        {
            _bool_components.at(name).SetValue(value);
        }
        else
        {
            AddValue(name, value);
        }
    }

    component_value_map<bool> &GetAllBoolValues()
    {
        return _bool_components;
    }

    //ETC ----------------------------------
    void *GetFunctionValue(std::string name)
    {
        return _functional_components.at(name).GetValue();
    }

    std::string GetName() const
    {
        return _name;
    }

    ptr<Component> GetSubcomponent(std::string name)
    {
        return _sub_components.at(name);
    }

    subcomponent_map<Component *> &GetSubcomponents()
    {
        return _sub_components;
    }

    void AddValue(std::string name, std::string value)
    {
        _string_components.insert(std::make_pair(name, ComponentValue<std::string>(name, value)));
    }

    void AddValue(std::string name, float value)
    {
        _float_components.insert(std::make_pair(name, ComponentValue<float>(name, value)));
    }

    void AddValue(std::string name, bool value)
    {
        _bool_components.insert(std::make_pair(name, ComponentValue<bool>(name, value)));
    }

    void AddSubcomponent(ptr<Component> sub_component)
    {
        _sub_components.insert(std::make_pair(sub_component->_name, sub_component));
    }

  protected:
    std::string _name;

  private:
    component_value_map<std::string> _string_components;
    component_value_map<float> _float_components;
    component_value_map<void *> _functional_components;
    component_value_map<bool> _bool_components;
    subcomponent_map<Component *> _sub_components;
};

#endif