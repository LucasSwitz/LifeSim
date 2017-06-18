#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include <list>
#include <unordered_map>
#include "src/system/ScriptableSystem.h"
#include "src/utils/ScriptFactory.h"

class SystemController : public ScriptFactory<ScriptableSystem>
{
  public:
    ScriptableSystem *Configure(std::string full_script_path, std::string scriptable_name) override
    {
        ScriptableSystem *new_system = new ScriptableSystem();
        new_system->LoadScript(LUA_STATE, full_script_path, scriptable_name);
        return new_system;
    }

    void AddScript(Preamble &pre, ScriptableSystem *scriptable_object) override
    {
        _system_directory.insert(std::make_pair(scriptable_object->GetName(), scriptable_object));
    }

    void Init()
    {
        for (auto it = _system_directory.begin(); it != _system_directory.end(); it++)
        {
            System *current_system = it->second;
            AddToSystemExecutionSequence(current_system);
        }
    }

    void AddToSystemExecutionSequence(System *system)
    {
        std::list<System *>::iterator insert_position = _systems_execution_sequence.end();

        //Make sure system isn't already added
        auto it = std::find(_systems_execution_sequence.begin(),
                            _systems_execution_sequence.end(),
                            system);

        if (it == _systems_execution_sequence.end())
        {
            std::string system_before_name = system->GetAfter();

            //After is defined
            if (!system_before_name.empty())
            {
                System *before_system = GetSystem(system_before_name);

                //previous system is a real system
                if (before_system)
                {
                    auto it = std::find(_systems_execution_sequence.begin(),
                                        _systems_execution_sequence.end(),
                                        before_system);

                    //previous system is already in Sequence
                    if (it != _systems_execution_sequence.end())
                    {
                        insert_position = std::next(it, 1);
                    }

                    //previous system is not in sequence
                    else
                    {
                        AddToSystemExecutionSequence(before_system);

                        auto it = std::find(_systems_execution_sequence.begin(),
                                            _systems_execution_sequence.end(),
                                            before_system);

                        insert_position = std::next(it, 1);
                    }
                }
            }
            _systems_execution_sequence.insert(insert_position, system);
        }
    }

    System *GetSystem(std::string name)
    {
        auto it = _system_directory.find(name);

        if (it == _system_directory.end())
            return nullptr;

        return _system_directory.at(name);
    }

    static SystemController *Instance()
    {
        static SystemController instance("/home/lucas/Desktop/LifeSim/lua_scripts/systems", "System");

        return &instance;
    }

    const System *GetSystemInExecutionSequenceAt(int index)
    {
        std::list<System *>::iterator it = std::next(_systems_execution_sequence.begin(), index);
        return *it;
    }

    int GetSequenceSize()
    {
        return _systems_execution_sequence.size();
    }

  protected:
    SystemController(std::string system_scripts_path, std::string script_type) : ScriptFactory<ScriptableSystem>(system_scripts_path, script_type, true){};

    std::list<System *> _systems_execution_sequence;
    std::unordered_map<std::string, System *> _system_directory;
};

#endif