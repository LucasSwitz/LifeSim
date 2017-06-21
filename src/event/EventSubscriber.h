#ifndef EVENTSUBSCRIBER_H
#define EVENTSUBSCRIBER_H

class EventSubscriber
{
    virtual void OnEvent(Event& e);

    virtual std::list<Subscription> GetSubscriptions();

};
#endif