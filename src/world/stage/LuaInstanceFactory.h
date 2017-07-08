#ifndef LUAINSTANCEFACTORY_H
#define LUAINSTANCEFACTORY_H

#include "src/utils/ScriptFactory.h"
#include "src/world/stage/LuaInstance.h"

class LuaInstanceFactory : public ScriptFactory<std::string>
{
  public:
  bool InstancePrototypeExists(std::string name);
  bool InstancePrototypeExists(int id);
  Instance* GetInstance(std::string name);
  Instance* GetInstance(int id);
  void AddScript(Preamble &pre, std::string script_path) override;

  void Reset() override;

   static LuaInstanceFactory* Inst() //can't name this Instance
  {
    static LuaInstanceFactory instance("/home/pabu/Desktop/LifeSim/lua_scripts/instances", "Instance");

    return &instance;
  }

protected:
  LuaInstanceFactory(std::string instance_scripts_path, std::string script_type) 
                        : ScriptFactory<std::string>(instance_scripts_path, script_type){};
    
private:    
    std::unordered_map<int, std::string> _instance_directory;
    std::unordered_map<std::string, int> _instance_name_to_id_directory;
    std::unordered_map<int, std::string> _instance_id_to_name_directory;

};

#endif
