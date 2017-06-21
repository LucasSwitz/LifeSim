#ifndef COMPONENTUSER_H
#define COMPONENTUSER_H

#include "src/component/Component.h"

class ComponentUserBase;

class ComponentUser
{
  public:
    void RemoveComponent(std::string name);
    bool HasComponent(std::string name);
    void AddComponent(Component *component);
    Component *GetComponent(std::string name);

  protected:
      std::unordered_map<std::string, Component*> _components;
};
#endif