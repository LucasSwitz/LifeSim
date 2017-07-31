#ifndef ENGINEEVENTMANAGER_H
#define ENGINEEVENTMANAGER_H

#include "src/event/EventManager.h"

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