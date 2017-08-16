#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include <list>
#include <chrono>
#include <mutex>

#include "src/system/SystemFactory.h"
#include "src/utils/logging/Logging.h"
#include "src/event/EventSubscriber.h"
#include "src/event/EventType.h"

/**
  Factory that loads all systems and orders their execution accordingly. 
  This factory should be seperated from the controller.
**/

class SystemController : public EventSubscriber
{
  friend class GameState;

public:
  SystemController(const SystemController &system_controller)
  {
    const std::list<System *> &systems = system_controller.GetExecutionSequence();

    for (auto it = systems.begin(); it != systems.end(); it++)
    {
      AddToSystemExecutionSequence((*it)->GetName());
    }
    MessageDispatch::Instance()->RegisterSubscriber(this);
  }

  void AddToSystemExecutionSequence(const std::string &system_name);
  void AddPassiveSystem(const std::string &system_name);
  void AddPassiveSystem(System *system);
  void AddToSystemExecutionSequence(System *system);
  std::list<System *>::iterator RemoveFromSystemExecutionSequence(const std::string &system_name);
  void MoveUp(std::string system_name);
  void MoveDown(std::string system_down);
  void Lock();
  void Unlock();

  const System *GetExecutionSequenceAt(int index);

  int GetSequenceSize();

  void Update(float seconds_since_last_update);

  void Reset()
  {
    LOG->LogInfo(1, "Systems Reset.");
    _systems_execution_sequence.clear();
    _passive_systems.clear();
  }

  static SystemController *Instance()
  {
    return _instance;
  }

  static void GiveOwnership(SystemController *instance)
  {
    _instance = instance;
  }

  const std::list<System *> &GetExecutionSequence() const;
  const std::list<System *> &GetPassiveSystems() const;
  std::list<System *> &GetExecutionSequenceMutable();
  std::list<System *> &GetPassiveSystemsMutable();

  //Inherited from EventSubscriber
  void OnEvent(Event &e);
  std::list<Subscription> GetSubscriptions();

protected:
  SystemController()
  {
    
  }

  std::list<System *> _systems_execution_sequence;
  std::list<System *> _passive_systems;

private:
  class SystemNameComparator
  {
  public:
    explicit SystemNameComparator(std::string name) : _name(name) {}
    inline bool operator()(System *&s)
    {
      return s->GetName().compare(_name) == 0;
    }

  private:
    std::string _name;
  };

  void
  MoveUp(System *system_name);
  void MoveDown(System *system_down);
  static SystemController *_instance;
  std::mutex _system_lock;
};

#endif