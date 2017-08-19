#ifndef SYSTEMFACTORY_H
#define SYSTEMFACTORY_H

#include <unordered_map>
#include "src/system/ScriptableSystem.h"
#include "src/utils/ScriptFactory.h"

/**
    Factory for all System classes. Systems can be retrieved by supplying a valid name.
**/

class SystemFactory : public ScriptFactory<std::string>
{
public:
  bool SystemExists(std::string name);
  System *GetSystem(std::string name);
  void AddScript(Preamble &pre, std::string scriptable_object) override;

  void Reset() override
  {
    _system_directory.clear();
  }

  static SystemFactory *Instance()
  {
    static SystemFactory instance("/home/lucas/Desktop/LifeSim/res/lua_scripts/systems", "System");

    return &instance;
  }

  std::unordered_map<std::string, std::string> &GetAllSystems();

protected:
  SystemFactory(std::string system_scripts_path, std::string script_type)
      : ScriptFactory<std::string>(system_scripts_path, script_type){};

private:
  std::unordered_map<std::string, std::string> _system_directory;
};

#endif