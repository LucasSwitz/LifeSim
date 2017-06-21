#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "src/event/Subscription.h"
#include "src/event/Event.h"

class EventManager
{
public:

    void LaunchEvent(Event& e);

    void RegisterSubscriber(Subscriber* sub);

    static EventManager* Instance()
    {
        static EventManager instance;
        return &instance;
    }

private:
    std::unordered_map<int, unordered_map<int, std::list<Subscriber*>>> _subscription_registry;

};
#endif