#ifndef EVENTSUBSCRIBER_H
#define EVENTSUBSCRIBER_H

#include <list>
#include "src/event/Subscription.h"

class Event;

class EventSubscriber
{
    public:
    virtual void OnEvent(Event& e){};
    virtual std::list<Subscription> GetSubscriptions(){};
};
#endif