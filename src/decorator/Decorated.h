#ifndef DECORATED_H
#define DECORATED_H

#include "src/decorator/EventHandlingDecorator.h"
#include "src/decorator/ComponentsDecorator.h"
#include "src/event/EventManager.h"
class Decorated
{
  public:
    void HasEventHandling();
    void HasComponents();

    void AddEventHandling(EventHandlingDecorator *d)
    {
        _event_handler = d;
        EventManager::Instance()->RegisterSubscriber(_event_handler); //maybe change this to something more dynamic later;
    };

    void AddComponents(ComponentsDecorator *d)
    {
        _components = d;
    };

  private:
    EventHandlingDecorator *_event_handler = nullptr;
    ComponentsDecorator *_components = nullptr;
};

#endif