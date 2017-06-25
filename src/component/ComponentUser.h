#ifndef COMPONENTUSER_H
#define COMPONENTUSER_H

#include <iostream>
#include "src/component/Component.h"

class ComponentUserBase;

class ComponentUser
{
  public:
    void AddComponent(Component *component);
    void RemoveComponent(std::string name);
    bool HasComponent(std::string name);

    Component* GetComponent(std::string name);

    std::string GetComponentValueString (std::string component_name, std::string component_name_value);
    void SetComponentValueString (std::string component_name, std::string component_name_value, std::string value);

    float GetComponentValueFloat (std::string component_name, std::string component_name_value);
    void SetComponentValueFloat (std::string component_name, std::string component_name_value, float value);

    void CallFunction(std::string component_name, std::string value_name);

    virtual ~ComponentUser(){};
  protected:
      std::unordered_map<std::string, Component*> _components;
};
#endif