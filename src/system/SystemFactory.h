#ifndef SYSTEMFACTORY_H
#define SYSTEMFACTORY_H

#include <unordered_map>
#include "src/system/ScriptableSystem.h"
#include "src/utils/ScriptFactory.h"

class SystemFactory : public ScriptFactory<ScriptableSystem>
{
public:
  bool SystemExists(std::string name);
  System *GetSystem(std::string name);
  void AddScript(Preamble &pre, ScriptableSystem *scriptable_object) override;
  ScriptableSystem *Configure(std::string full_script_path, std::string scriptable_name) override;

    void Reset() override
    {
        _system_directory.clear();
    }

   static SystemFactory* Instance()
  {
    static SystemFactory instance("/home/pabu/Desktop/LifeSim/lua_scripts/systems", "System");

    return &instance;
  }

protected:
  SystemFactory(std::string system_scripts_path, std::string script_type) : ScriptFactory<ScriptableSystem>(system_scripts_path, script_type, true){};
    
private:    
    std::unordered_map<std::string, System *> _system_directory;


};

#endif