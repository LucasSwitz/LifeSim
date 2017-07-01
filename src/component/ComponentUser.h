#ifndef COMPONENTUSER_H
#define COMPONENTUSER_H

#include <iostream>
#include "src/component/Component.h"

/**
  Component User's simply maintain a list of active components, and also register themselves
  with the ComponentUserBase. ComponentUser offers convients functions that allow for direct
  access to one of thier component's values.
**/

class ComponentUserBase;

class ComponentUser
{
  public:
    void AddComponent(Component *component);
    void RemoveComponent(std::string name);
    bool HasComponent(std::string name) const;

    Component* GetComponent(std::string name);

    std::string GetComponentValueString (std::string component_name, std::string component_name_value) const;
    void SetComponentValueString (std::string component_name, std::string component_name_value, std::string value);

    float GetComponentValueFloat (std::string component_name, std::string component_name_value) const; 
    void SetComponentValueFloat (std::string component_name, std::string component_name_value, float value);

    void CallFunction(std::string component_name, std::string value_name);

    virtual ~ComponentUser(){};
  protected:
      std::unordered_map<std::string, Component*> _components;
};
#endif