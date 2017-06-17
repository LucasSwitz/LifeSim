#ifndef COMPONENT_H
#define COMPONENT_H

#include <unordered_map>

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

        T GetValue() const
        {
            return value;
        }

        std::string GetName() const
        {
            return name;
        }

        std::string name;
        T value;
    };

    void SetValue(std::string name, std::string value)
    {
        _string_components.at(name).SetValue(value);
    }

    void SetValue(std::string name, float value)
    {
        _float_components.at(name).SetValue(value);
    }

    float GetFloatValue(std::string name) const
    {
        return _float_components.at(name).GetValue();
    }

    std::string GetStringValue(std::string name) const
    {
        return _string_components.at(name).GetValue();
    }

    std::string GetName() const
    {
        return _name;
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

    Component(std::string name="") : _name(name){};

  private:
    std::unordered_map<std::string, ComponentValue<std::string>> _string_components;
    std::unordered_map<std::string, ComponentValue<float>> _float_components;
    std::string _name;
};

#endif