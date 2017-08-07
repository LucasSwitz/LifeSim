#ifndef EVENTSUBSCRIBER_H
#define EVENTSUBSCRIBER_H

#include <list>
#include "src/event/Subscription.h"

/**
    Purpose: The EventSubscriber interface allows classes to subscribe the specfied events.
             Instances of classes that implement this interface can be registered with an EventManager
             to recieve events.
**/

class Event;

class EventSubscriber
{
    public:
    virtual void OnEvent(Event& e){};
    virtual std::list<Subscription> GetSubscriptions(){};
};
#endif