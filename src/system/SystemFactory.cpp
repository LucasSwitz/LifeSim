#include "SystemFactory.h"

ScriptableSystem *SystemFactory::Configure(std::string full_script_path, std::string scriptable_name)
{
    ScriptableSystem *new_system = new ScriptableSystem();
    new_system->LoadScript(LUA_STATE, full_script_path, scriptable_name);
    return new_system;
}

System *SystemFactory::GetSystem(std::string name)
{
    if (!SystemExists(name))
    {
        std::cout << "System does not exists: " << name << std::endl;
        return nullptr;
    }

    return _system_directory.at(name);
}

bool SystemFactory::SystemExists(std::string name)
{
    return _system_directory.find(name) != _system_directory.end();
}

void SystemFactory::AddScript(Preamble &pre, ScriptableSystem *scriptable_object)
{
    _system_directory.insert(std::make_pair(scriptable_object->GetName(), scriptable_object));
}