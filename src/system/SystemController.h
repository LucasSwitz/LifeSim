#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include <list>
#include <chrono>
#include <mutex>

#include "src/system/SystemFactory.h"
#include "src/utils/logging/Logging.h"
#include "src/event/EventSubscriber.h"
#include "src/event/EventType.h"
#include "src/event/EventManager.h"
#include "src/event/messaging/MessageDispatcher.h"

/**
  Factory that loads all systems and orders their execution accordingly. 
  This factory should be seperated from the controller.
**/
class GameState;

template <typename T>
class SystemController : public EventSubscriber, public MessageDispatcher
{
  friend class GameState;

public:
  typedef ptr<System<T>> sys_ptr;
  typedef std::list<sys_ptr> system_list;

  SystemController()
  {
    
  }

  SystemController(const SystemController &system_controller)
  {
    const system_list &systems = system_controller.GetExecutionSequence();

    for (auto it = systems.begin(); it != systems.end(); it++)
    {
      AddToSystemExecutionSequence((*it)->GetName());
    }
  }

  void AddPassiveSystem(const std::string &system_name)
  {
    System<T> *system = SystemFactory::Instance()->GetSystem<T>(system_name);
    AddPassiveSystem(sys_ptr(system));
  }

  typename system_list::iterator RemoveFromSystemExecutionSequence(const std::string &system_name)
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

  void AddPassiveSystem(sys_ptr system)
  {
    LOG->LogInfo(1, "Adding Passive System: %s \n", system->GetName().c_str());
    _passive_systems.push_back(system);
  }

  void AddToSystemExecutionSequence(const std::string &system_name)
  {
    sys_ptr system = sys_ptr(SystemFactory::Instance()->GetSystem<T>(system_name));
    AddToSystemExecutionSequence(system);
  }

  void AddToSystemExecutionSequence(sys_ptr system)
  {
    typename system_list::iterator insert_position = _systems_execution_sequence.end();

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
        sys_ptr before_system = sys_ptr(SystemFactory::Instance()->GetSystem<T>(system_before_name));

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
            AddToSystemExecutionSequence(sys_ptr(before_system));

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
        if (IsAssignedToDispatch())
          GetAssignedDispatch()->RegisterSubscriber(system.get());
      }
    }
  }

  const sys_ptr GetExecutionSequenceAt(int index)
  {
    typename system_list::iterator it =
        std::next(_systems_execution_sequence.begin(), index);
    return *it;
  }

  int GetSequenceSize()
  {
    return _systems_execution_sequence.size();
  }

  const system_list &GetExecutionSequence() const
  {
    return _systems_execution_sequence;
  }

  system_list &GetExecutionSequenceMutable()
  {
    return _systems_execution_sequence;
  }

  const system_list &GetPassiveSystems() const
  {
    return _passive_systems;
  }

  system_list &GetPassiveSystemsMutable()
  {
    return _passive_systems;
  }

  void MoveUp(std::string system_name)
  {
    if (SystemFactory::Instance()->SystemExists(system_name))
    {
      System<T> *system = SystemFactory::Instance()->GetSystem<T>(system_name);
      MoveUp(sys_ptr(system));
    }
    else
    {
      std::cout << "System does not exists" << std::endl;
    }
  }

  void MoveUp(sys_ptr system)
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

  void MoveDown(std::string system_name)
  {
    if (SystemFactory::Instance()->SystemExists(system_name))
    {
      System<T> *system = SystemFactory::Instance()->GetSystem<T>(system_name);
      MoveDown(sys_ptr(system));
    }
  }

  void MoveDown(sys_ptr system)
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

  void Lock()
  {
    _system_lock.lock();
  }

  void Unlock()
  {
    _system_lock.unlock();
  }

  void OnEvent(Event &e)
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

  std::list<Subscription> GetSubscriptions()
  {
    std::list<Subscription> subs = {Subscription(EventType::START_SYSTEM_EVENT),
                                    Subscription(EventType::STOP_SYSTEM_EVENT)};

    return subs;
  }

  void Update(float seconds_since_last_update, T* pass)
  {
    for (auto it = _systems_execution_sequence.begin(); it != _systems_execution_sequence.end(); it++)
    {
      if ((*it)->IsPaused())
        continue;

      auto start_time = std::chrono::high_resolution_clock::now();

      (*it)->Update(seconds_since_last_update, pass);

      auto end_time = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> elapsed =
          std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
      (*it)->SetLastRuntime(elapsed.count() * 1000);
    }
  }

  void Reset()
  {
    LOG->LogInfo(1, "Systems Reset.");
    _systems_execution_sequence.clear();
    _passive_systems.clear();
  }

  bool HasSystem(const std::string& system_name)
  {
    
    return std::find_if(_systems_execution_sequence.begin(),
                           _systems_execution_sequence.end(),
                           SystemNameComparator(system_name)) != _systems_execution_sequence.end() ||
           std::find_if(_passive_systems.begin(),
                           _passive_systems.end(),
                           SystemNameComparator(system_name)) != _passive_systems.end();
  }

protected:
  system_list _systems_execution_sequence;
  system_list _passive_systems;

private:
  class SystemNameComparator
  {
  public:
    explicit SystemNameComparator(std::string name) : _name(name) {}
    inline bool operator()(sys_ptr s)
    {
      return s->GetName().compare(_name) == 0;
    }

  private:
    std::string _name;
  };

  std::mutex _system_lock;
};

#endif