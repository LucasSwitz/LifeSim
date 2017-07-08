#include "src/world/stage/LuaStageFactory.h"

void LuaStageFactory::AddScript(Preamble &pre, std::string script_path)
{
    int prototype_id = std::stoi(pre.GetFlag("ID"));
    std::string prototype_name = pre.GetFlag("Name");

    _stage_directory.insert(std::make_pair(prototype_id, script_path));
    _stage_id_to_name_directory.insert(std::make_pair(prototype_id, prototype_name));
    _stage_name_to_id_directory.insert(std::make_pair(prototype_name, prototype_id));
}

Stage* LuaStageFactory::GetStage(int id)
{
    if(!StagePrototypeExists(id))
    {
        std::cout << "Stage Does Not Exists: " << id << std::endl;
        return nullptr;
    }

    LuaStage *new_stage = new LuaStage();
    new_stage->LoadFromFile(LUA_STATE, _stage_directory.at(id), _stage_id_to_name_directory.at(id));
    return new_stage;
}

Stage* LuaStageFactory::GetStage(std::string name)
{
    if(!StagePrototypeExists(name))
    {   
        std::cout << "Stage Does Not Exists: " << name << std::endl;
        return nullptr;
    }
    
    return this->GetStage(_stage_name_to_id_directory.at(name));
}

bool LuaStageFactory::StagePrototypeExists(int id)
{
    return _stage_directory.find(id) != _stage_directory.end();
}

bool LuaStageFactory::StagePrototypeExists(std::string name)
{
    return _stage_name_to_id_directory.find(name) != _stage_name_to_id_directory.end();
}

void LuaStageFactory::Reset()
{
    _stage_directory.clear();
    _stage_id_to_name_directory.clear();
    _stage_name_to_id_directory.clear();
}