#include "SystemFactory.h"

System *SystemFactory::GetSystem(std::string name)
{
    if (!SystemExists(name))
    {
        throw AssetNotFoundException(name);
    }

    ScriptableSystem *new_system = new ScriptableSystem();
    new_system->LoadScript(LUA_STATE, _system_directory.at(name), name);
    return new_system;
}

bool SystemFactory::SystemExists(std::string name)
{
    return _system_directory.find(name) != _system_directory.end();
}

void SystemFactory::AddScript(Preamble &pre, std::string scriptable_object)
{
    _system_directory.insert(std::make_pair(pre.GetFlag("Name"), scriptable_object));
}
 
std::unordered_map<std::string, std::string>& SystemFactory::GetAllSystems()
{
    return _system_directory;
}
