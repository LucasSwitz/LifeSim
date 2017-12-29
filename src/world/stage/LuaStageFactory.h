#ifndef LUASTAGEFACTORY_H
#define LUASTAGEFACTORY_H


#include "src/utils/ResourceFactory.h"
#include "src/world/stage/LuaStage.h"

/**
    Purpose: LuaStageFactory can be used to create Lua defined Stages by supplying 
             a valid name or ID.
**/
class LuaStageFactory : public ResourceFactory<std::string>
{

  public:
  bool StagePrototypeExists(std::string name);
  bool StagePrototypeExists(int id);
  Stage* GetStage(std::string name);
  Stage* GetStage(int id);
  void AddResource(Preamble &pre, std::string script_path) override;

  void Reset() override;

   static LuaStageFactory* Instance()
  {
    static LuaStageFactory instance("Stage");

    return &instance;
  }

protected:
  LuaStageFactory(std::string script_type) 
                        : ResourceFactory<std::string>(script_type){};
    
private:    
    std::unordered_map<int, std::string> _stage_directory;
    std::unordered_map<std::string, int> _stage_name_to_id_directory;
    std::unordered_map<int, std::string> _stage_id_to_name_directory;

};

#endif
