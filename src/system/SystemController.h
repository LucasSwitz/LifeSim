#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include <list>
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
  void AddToSystemExecutionSequence(System *system);

  const System *GetSystemInExecutionSequenceAt(int index);

  int GetSequenceSize();

  void Update(double seconds_since_last_update);

  void Reset()
  {
    _systems_execution_sequence.clear();
  }

  static SystemController *Instance()
  {
    static SystemController instance;

    return &instance;
  }

protected:
  SystemController(){};

  std::list<System *> _systems_execution_sequence;
private:
};

#endif