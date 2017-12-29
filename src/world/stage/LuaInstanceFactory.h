#ifndef LUAINSTANCEFACTORY_H
#define LUAINSTANCEFACTORY_H

#include "src/utils/ResourceFactory.h"
#include "src/world/stage/LuaInstance.h"

/**
  Purpose: LuaInstanceFactory can be used to create Lua defined instances by supplying
           a valid name or ID.
**/
class LuaInstanceFactory : public ResourceFactory<std::string>
{
  public:
  bool InstancePrototypeExists(std::string name);
  bool InstancePrototypeExists(int id);
  Instance* GetInstance(std::string name);
  Instance* GetInstance(int id);
  void AddResource(Preamble &pre, std::string script_path) override;
  void AddResource(std::string& name, int& id, std::string& script_path);
  void Reset() override;
  int LowestUnassignedKey();

   static LuaInstanceFactory* Inst() //can't name this Instance :(
  {
    static LuaInstanceFactory instance("Instance");

    return &instance;
  }

protected:
  LuaInstanceFactory(std::string script_type) 
                        : ResourceFactory<std::string>(script_type){};
    
private:    
    std::unordered_map<int, std::string> _instance_directory;
    std::unordered_map<std::string, int> _instance_name_to_id_directory;
    std::unordered_map<int, std::string> _instance_id_to_name_directory;

};

#endif
