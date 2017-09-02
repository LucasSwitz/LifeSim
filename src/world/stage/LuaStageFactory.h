#ifndef LUASTAGEFACTORY_H
#define LUASTAGEFACTORY_H


#include "src/utils/ScriptFactory.h"
#include "src/world/stage/LuaStage.h"

/**
    Purpose: LuaStageFactory can be used to create Lua defined Stages by supplying 
             a valid name or ID.
**/
class LuaStageFactory : public ScriptFactory<std::string>
{

  public:
  bool StagePrototypeExists(std::string name);
  bool StagePrototypeExists(int id);
  Stage* GetStage(std::string name);
  Stage* GetStage(int id);
  void AddScript(Preamble &pre, std::string script_path) override;

  void Reset() override;

   static LuaStageFactory* Instance()
  {
    static LuaStageFactory instance("/home/lucas/Desktop/LifeSim/lua_scripts/world/stages", "Stage");

    return &instance;
  }

protected:
  LuaStageFactory(std::string stage_scripts_path, std::string script_type) 
                        : ScriptFactory<std::string>(stage_scripts_path, script_type){};
    
private:    
    std::unordered_map<int, std::string> _stage_directory;
    std::unordered_map<std::string, int> _stage_name_to_id_directory;
    std::unordered_map<int, std::string> _stage_id_to_name_directory;

};

#endif
