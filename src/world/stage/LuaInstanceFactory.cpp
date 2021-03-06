#include "src/world/stage/LuaInstanceFactory.h"

void LuaInstanceFactory::AddResource(Preamble &pre, std::string script_path)
{
    std::string prototype_name = pre.GetFlag("Name");
    int prototype_id = std::stoi(pre.GetFlag("ID"));

    AddResource(prototype_name, prototype_id, script_path);
}

void LuaInstanceFactory::AddResource(std::string &prototype_name, int &prototype_id, std::string &script_path)
{
    _instance_directory.insert(std::make_pair(prototype_id, script_path));
    _instance_id_to_name_directory.insert(std::make_pair(prototype_id, prototype_name));
    _instance_name_to_id_directory.insert(std::make_pair(prototype_name, prototype_id));
}

Instance *LuaInstanceFactory::GetInstance(int id)
{
    if (!InstancePrototypeExists(id))
    {
        throw AssetNotFoundException("Instance: " + std::to_string(id));
    }

    LuaInstance *new_instance = new LuaInstance(id);
    new_instance->LoadFromFile(LUA_STATE, _instance_directory.at(id), _instance_id_to_name_directory.at(id));
    return new_instance;
}

Instance *LuaInstanceFactory::GetInstance(std::string name)
{
    if (!InstancePrototypeExists(name))
    {
        throw AssetNotFoundException("Instance: " + name);
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

int LuaInstanceFactory::LowestUnassignedKey()
{
    //TODO: Change this to an std::map and just start counting
    int size = _instance_directory.size();

    if (size == 0)
        return 0;

    std::vector<int> ids(size);

    for (auto it = _instance_directory.begin(); it != _instance_directory.end(); it++)
    {
        int id = it->first;

        if (id >= size || id < 0)
            continue;

        ids[id] = 1;
    }

    for (int i = 0; i < size; i++)
    {
        if (ids[i] == 0)
        {
            return i;
        }
    }
}

void LuaInstanceFactory::Reset()
{
    _instance_directory.clear();
    _instance_id_to_name_directory.clear();
    _instance_name_to_id_directory.clear();
}