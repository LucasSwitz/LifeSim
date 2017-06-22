#ifndef EVENTHANDLINGDECORATOR_H
#define EVENTHANDLINGDECORATOR_H

#include "src/event/EventSubscriber.h"
#include "src/event/Event.h"

class EventHandlingDecorator : public EventSubscriber
{
  public:
    virtual void OnEvent(Event &e) override {}
    virtual std::list<Subscription> GetSubscriptions() override
    {
        std::list<Subscription> empty;
        return empty;
    }
};

#endif