#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include <list>
#include <chrono>

#include "src/system/SystemFactory.h"
#include "src/utils/logging/Logging.h"
/**
  Factory that loads all systems and orders their execution accordingly. 
  This factory should be seperated from the controller.
**/

class SystemController
{
public:
  void AddToSystemExecutionSequence(const std::string& system_name);
  void AddPassiveSystem(const std::string& system_name);
  void AddPassiveSystem(System * system);
  void AddToSystemExecutionSequence(System *system);
  void MoveUp(std::string system_name);
  void MoveDown(std::string system_down);


  const System *GetSystemInExecutionSequenceAt(int index);

  int GetSequenceSize();

  void Update(float seconds_since_last_update);

  void Reset()
  {
    LOG->LogInfo(1,"Systems Reset.");
    _systems_execution_sequence.clear();
    _passive_systems.clear();
  }

  static SystemController *Instance()
  {
    static SystemController instance;

    return &instance;
  }

  std::list<System*>& GetSystemInExecutionSequence();
  std::list<System*>& GetPassiveSystems();


protected:
  SystemController(){};

  std::list<System *> _systems_execution_sequence;
  std::list<System *> _passive_systems;
private:
  void MoveUp(System* system_name);
  void MoveDown(System* system_down);

};

#endif