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

typedef std::list<ptr<System>> system_list;

class SystemController : public EventSubscriber, public MessageDispatcher
{
  friend class GameState;

public:
  SystemController(EventManager& msgd)
  {
    msgd.RegisterSubscriber(this);
  }

  SystemController(const SystemController &system_controller)
  {
    const system_list &systems = system_controller.GetExecutionSequence();

    for (auto it = systems.begin(); it != systems.end(); it++)
    {
      AddToSystemExecutionSequence((*it)->GetName());
    }
  }

  void AddToSystemExecutionSequence(const std::string &system_name);
  void AddPassiveSystem(const std::string &system_name);
  void AddPassiveSystem(ptr<System> system);
  void AddToSystemExecutionSequence(ptr<System> system);
  system_list::iterator RemoveFromSystemExecutionSequence(const std::string &system_name);
  void MoveUp(std::string system_name);
  void MoveDown(std::string system_down);
  void Lock();
  void Unlock();

  const ptr<System> GetExecutionSequenceAt(int index);

  int GetSequenceSize();

  void Update(float seconds_since_last_update, ptr<GameState> g);

  void Reset()
  {
    LOG->LogInfo(1, "Systems Reset.");
    _systems_execution_sequence.clear();
    _passive_systems.clear();
  }

  const system_list &GetExecutionSequence() const;
  const system_list &GetPassiveSystems() const;
  system_list &GetExecutionSequenceMutable();
  system_list &GetPassiveSystemsMutable();

  //Inherited from EventSubscriber
  void OnEvent(Event &e);
  std::list<Subscription> GetSubscriptions();

protected:
  SystemController()
  {
    
  }

  system_list _systems_execution_sequence;
  system_list _passive_systems;

private:
  class SystemNameComparator
  {
  public:
    explicit SystemNameComparator(std::string name) : _name(name) {}
    inline bool operator()(ptr<System> s)
    {
      return s->GetName().compare(_name) == 0;
    }

  private:
    std::string _name;
  };

  void MoveUp(ptr<System> system_name);
  void MoveDown(ptr<System> system_down);
  
  std::mutex _system_lock;
};

#endif