#include "SystemController.h"

void SystemController::AddPassiveSystem(const std::string& system_name)
{
    System* system = SystemFactory::Instance()->GetSystem(system_name);
    AddPassiveSystem(system);
}

void SystemController::AddPassiveSystem(System* system)
{
    LOG->LogInfo(1,"Adding Passive System: %s \n",system->GetName().c_str());
    _passive_systems.push_back(system);
}

void SystemController::AddToSystemExecutionSequence(const std::string& system_name)
{
    System* system = SystemFactory::Instance()->GetSystem(system_name);
    AddToSystemExecutionSequence(system);
}

void SystemController::AddToSystemExecutionSequence(System *system)
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
            System *before_system = SystemFactory::Instance()->GetSystem(system_before_name);

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
        
        if(system)
        {
            LOG->LogInfo(1,"Adding System to Execution: %s \n",system->GetName().c_str());
            _systems_execution_sequence.insert(insert_position, system);
        }
    }
}

const System *SystemController::GetSystemInExecutionSequenceAt(int index)
{
    std::list<System *>::iterator it = std::next(_systems_execution_sequence.begin(), index);
    return *it;
}

int SystemController::GetSequenceSize()
{
    return _systems_execution_sequence.size();
}

void SystemController::Update(double seconds_since_last_update)
{
    for (auto it = _systems_execution_sequence.begin(); it != _systems_execution_sequence.end(); it++)
    {
        (*it)->Update(seconds_since_last_update);
    }
}