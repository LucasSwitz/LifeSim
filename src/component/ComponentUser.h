#ifndef COMPONENTUSER_H
#define COMPONENTUSER_H

#include <iostream>
#include "src/component/Component.h"
#include "src/component/ComponentUserType.h"
#include "src/component/ComponentUserListener.h"

/**
  Component User's simply maintain a list of active components, and also register themselves
  with the ComponentUserBase. ComponentUser offers convients functions that allow for direct
  access to one of thier component's values.
**/

class ComponentUserBase;

class ComponentUser
{
  friend class GameState;

public:
  typedef std::unordered_map<std::string, ptr<Component>> component_map;

  ComponentUser(int type, int id = -1) : _id(id)
  {
    if (_id == -1)
    {
      _id = last_id++;
    }
  };

  int ID() const;
  int Type() const;

  void AddComponent(ptr<Component> component);
  void AddComponentValue(const std::string &component_name, const std::string &value_name, std::string value);
  void AddComponentValue(const std::string &component_name, const std::string &value_name, bool value);
  void AddComponentValue(const std::string &component_name, const std::string &value_name, float value);
  void RemoveComponent(std::string name);
  bool HasComponent(std::string name) const;
  void DisableComponent(std::string name);
  void EnableComponent(std::string name);
  void DisableAll();
  void EnableAll();
  void EnableAll(ComponentUserBase &component_user_base);

  void SetListener(ComponentUserListener* listener);

  ptr<Component> GetComponent(std::string name);

  std::string GetComponentValueString(std::string component_name, std::string component_name_value) const;
  void SetComponentValueString(std::string component_name, std::string component_name_value, std::string value);

  float GetComponentValueFloat(std::string component_name, std::string component_name_value) const;
  void SetComponentValueFloat(std::string component_name, std::string component_name_value, float value);

  bool GetComponentValueBool(std::string component_name, std::string component_name_value);
  void SetComponentValueBool(std::string component_name, std::string component_name_value, bool value);
  void CallFunction(std::string component_name, std::string value_name);

  std::unordered_map<std::string, ptr<Component>> &GetAllComponents();
  virtual ~ComponentUser();
  static int last_id;

  ComponentUserListener* const GetComponentListener() const
  {
    return _listener;
  }

protected:
  component_map _components;
  ComponentUserListener* _listener = nullptr;
  bool _is_hidden;
  void SetID(int id);
  int _id;
  int _type;
};
#endif