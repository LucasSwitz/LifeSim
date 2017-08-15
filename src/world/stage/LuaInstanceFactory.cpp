#include "src/world/stage/LuaInstanceFactory.h"

void LuaInstanceFactory::AddScript(Preamble &pre, std::string script_path)
{
    std::string prototype_name = pre.GetFlag("Name");
    int prototype_id = std::stoi(pre.GetFlag("ID"));

    AddScript(prototype_name, prototype_id,script_path);
}

void LuaInstanceFactory::AddScript(std::string& prototype_name, int& prototype_id, std::string& script_path)
{
    _instance_directory.insert(std::make_pair(prototype_id, script_path));
    _instance_id_to_name_directory.insert(std::make_pair(prototype_id, prototype_name));
    _instance_name_to_id_directory.insert(std::make_pair(prototype_name, prototype_id));
}

Instance* LuaInstanceFactory::GetInstance(int id)
{
    if(!InstancePrototypeExists(id))
    {
        std::cout << "Instance Does Not Exists: " << id << std::endl;
        return nullptr;
    }

    LuaInstance *new_instance = new LuaInstance(id);
    new_instance->LoadFromFile(LUA_STATE, _instance_directory.at(id), _instance_id_to_name_directory.at(id));
    return new_instance;
}

Instance* LuaInstanceFactory::GetInstance(std::string name)
{
    if(!InstancePrototypeExists(name))
    {   
        std::cout << "Instance Does Not Exists: " << name << std::endl;
        return nullptr;
    }
    
    return this->GetInstance(_instance_name_to_id_directory.at(name));
}

bool LuaInstanceFactory::InstancePrototypeExists(int id)
{
    return _instance_directory.find(id) != _instance_directory.end();
}

bool LuaInstanceFactory::InstancePrototypeExists(std::string name)
{
    return _instance_name_to_id_directory.find(name) != _instance_name_to_id_directory.end();
}

void LuaInstanceFactory::Reset()
{
    _instance_directory.clear();
    _instance_id_to_name_directory.clear();
    _instance_name_to_id_directory.clear();
}