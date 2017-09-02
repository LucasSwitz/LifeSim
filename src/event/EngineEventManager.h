#ifndef ENGINEEVENTMANAGER_H
#define ENGINEEVENTMANAGER_H

#include "src/event/EventManager.h"

/**
    Purpose: The EngineEventManager is an event manager for all engine specific operations.
            Unlike other EventManager implementations, the global EngineEventManager instance
            does not change throughout the engines operation.

**/
class EngineEventManager : public EventManager
{
  public:
    static EngineEventManager *Instance()
    {
      static EngineEventManager instance;
        return &instance;
    }    
};
#endif