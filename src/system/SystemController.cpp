#include "SystemController.h"

SystemController* SystemController::_instance = nullptr;

void SystemController::AddPassiveSystem(const std::string &system_name)
{
    System *system = SystemFactory::Instance()->GetSystem(system_name);
    AddPassiveSystem(system);
}

std::list<System*>::iterator SystemController::RemoveFromSystemExecutionSequence(const std::string& system_name)
{
    auto it = _systems_execution_sequence.begin();

    for(; it != _systems_execution_sequence.end(); it++)
    {
        if((*it)->GetName().compare(system_name) == 0)
        {
            it = _systems_execution_sequence.erase(it);
            break;
        }
    }

    return it;
}

void SystemController::AddPassiveSystem(System *system)
{
    LOG->LogInfo(1, "Adding Passive System: %s \n", system->GetName().c_str());
    _passive_systems.push_back(system);
}

void SystemController::AddToSystemExecutionSequence(const std::string &system_name)
{
    System *system = SystemFactory::Instance()->GetSystem(system_name);
    AddToSystemExecutionSequence(system);
}

void SystemController::AddToSystemExecutionSequence(System *system)
{
    std::list<System *>::iterator insert_position = _systems_execution_sequence.end();

    //Make sure system isn't already added
    auto it = std::find_if(_systems_execution_sequence.begin(),
                        _systems_execution_sequence.end(),
                        SystemNameComparator(system->GetName()));

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
                auto it = std::find_if(_systems_execution_sequence.begin(),
                                    _systems_execution_sequence.end(),
                                    SystemNameComparator(system_before_name));

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

        if (system)
        {
            LOG->LogInfo(1, "Adding System to Execution: %s \n", system->GetName().c_str());
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

void SystemController::Update(float seconds_since_last_update)
{
    for (auto it = _systems_execution_sequence.begin(); it != _systems_execution_sequence.end(); it++)
    {
        auto start_time = std::chrono::high_resolution_clock::now();

        (*it)->Update(seconds_since_last_update);

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
        (*it)->SetLastRuntime(elapsed.count() * 1000);
    }
}

const std::list<System *> &SystemController::GetSystemInExecutionSequence() const
{
    return _systems_execution_sequence;
}

const std::list<System *> &SystemController::GetPassiveSystems() const
{
    return _passive_systems;
}

void SystemController::MoveUp(std::string system_name)
{
    if (SystemFactory::Instance()->SystemExists(system_name))
    {
        System *system = SystemFactory::Instance()->GetSystem(system_name);
        MoveUp(system);
    }
    else
    {
        std::cout << "System does not exists" << std::endl;
    }
}

void SystemController::MoveUp(System *system)
{
    for (auto it = _systems_execution_sequence.begin(); it != _systems_execution_sequence.end(); it++)
    {
        auto next = std::next(it);
        if (next != _systems_execution_sequence.end())
        {
            if (*next == system)
            {
                std::swap(*it, *(next));
                return;
            };
        }
    }
}

void SystemController::MoveDown(std::string system_name)
{
    if (SystemFactory::Instance()->SystemExists(system_name))
    {
        System *system = SystemFactory::Instance()->GetSystem(system_name);
        MoveDown(system);
    }
}

void SystemController::MoveDown(System *system)
{
    for (auto it = _systems_execution_sequence.begin(); it != _systems_execution_sequence.end(); it++)
    {
        auto next = std::next(it);
        if (next != _systems_execution_sequence.end())
        {
            if (*it == system)
            {
                std::swap(*it, *(next));
                return;
            };
        }
    }
}

void SystemController::Lock()
{
    _system_lock.lock();
}

void SystemController::Unlock()
{
    _system_lock.unlock();
}
