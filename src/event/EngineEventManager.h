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
    static void GiveOwnership(EngineEventManager *dispatch)
    {
        _instance = dispatch;
    }

    static EngineEventManager *Instance()
    {
        return _instance;
    }

  private:
    static EngineEventManager *_instance;
};
#endif