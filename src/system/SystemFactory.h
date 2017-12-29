#ifndef SYSTEMFACTORY_H
#define SYSTEMFACTORY_H

#include <unordered_map>
#include "src/system/ScriptableSystem.h"
#include "src/utils/ResourceFactory.h"
#include "src/utils/Globals.h"

/**
    Factory for all System classes. Systems can be retrieved by supplying a valid name.
**/
class SystemFactory : public ResourceFactory<std::string>
{
public:

  template<typename T>
  System<T>* GetSystem(std::string name)
  {
    if (!SystemExists(name))
    {
      throw AssetNotFoundException(name);
    }

    ScriptableSystem<T> *new_system = new ScriptableSystem<T>();
    new_system->LoadScript(LUA_STATE, _system_directory.at(name), name);
    return new_system;
  }

  bool SystemExists(std::string name)
  {
    return _system_directory.find(name) != _system_directory.end();
  }

  void AddResource(Preamble &pre, std::string scriptable_object)
  {
    _system_directory.insert(std::make_pair(pre.GetFlag("Name"), scriptable_object));
  }

  std::unordered_map<std::string, std::string> &GetAllSystems()
  {
    return _system_directory;
  }

  void Reset() override
  {
    _system_directory.clear();
  }

  static SystemFactory *Instance()
  {
    static SystemFactory instance("System");

    return &instance;
  }

protected:
  SystemFactory(std::string script_type)
      : ResourceFactory<std::string>(script_type){};

private:
  std::unordered_map<std::string, std::string> _system_directory;
};

#endif