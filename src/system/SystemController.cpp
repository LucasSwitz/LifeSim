#include "SystemController.h"
#include "src/game/GameState.h"

void SystemController::AddPassiveSystem(const std::string &system_name)
{
    System *system = SystemFactory::Instance()->GetSystem(system_name);
    AddPassiveSystem(system);
}

std::list<System *>::iterator SystemController::RemoveFromSystemExecutionSequence(const std::string &system_name)
{
    auto it = _systems_execution_sequence.begin();

    for (; it != _systems_execution_sequence.end(); it++)
    {
        if ((*it)->GetName().compare(system_name) == 0)
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

            //Assign all systems to the message dispatch
            if(IsAssignedToDispatch())
                GetAssignedDispatch()->RegisterSubscriber(system);           
        }
    }
}

const System *SystemController::GetExecutionSequenceAt(int index)
{
    std::list<System *>::iterator it = std::next(_systems_execution_sequence.begin(), index);
    return *it;
}

int SystemController::GetSequenceSize()
{
    return _systems_execution_sequence.size();
}

void SystemController::Update(float seconds_since_last_update, GameState* g)
{
    for (auto it = _systems_execution_sequence.begin(); it != _systems_execution_sequence.end(); it++)
    {
        if ((*it)->IsPaused())
            continue;

        auto start_time = std::chrono::high_resolution_clock::now();

        (*it)->Update(seconds_since_last_update, g);

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
        (*it)->SetLastRuntime(elapsed.count() * 1000);
    }
}

const std::list<System *> &SystemController::GetExecutionSequence() const
{
    return _systems_execution_sequence;
}

std::list<System *> &SystemController::GetExecutionSequenceMutable()
{
    return _systems_execution_sequence;
}

const std::list<System *> &SystemController::GetPassiveSystems() const
{
    return _passive_systems;
}

std::list<System *> &SystemController::GetPassiveSystemsMutable()
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
            if ((*next)->GetName().compare(system->GetName()) == 0)
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
            if ((*it)->GetName().compare(system->GetName()) == 0)
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

void SystemController::OnEvent(Event &e)
{
    if (e.id == EventType::START_SYSTEM_EVENT)
    {
        std::vector<std::string> *system_names = e.InfoToType<std::vector<std::string> *>();

        for (std::string system_name : *system_names)
        {
            AddToSystemExecutionSequence(system_name);
        }

        delete system_names;
    }
    else if (e.id == EventType::STOP_SYSTEM_EVENT)
    {
        std::vector<std::string> *system_names = e.InfoToType<std::vector<std::string> *>();

        for (std::string system_name : *system_names)
        {
            RemoveFromSystemExecutionSequence(system_name);
        }

        delete system_names;
    }
}

std::list<Subscription> SystemController::GetSubscriptions()
{
    std::list<Subscription> subs = {Subscription(EventType::START_SYSTEM_EVENT),
                                    Subscription(EventType::STOP_SYSTEM_EVENT)};

    return subs;
}