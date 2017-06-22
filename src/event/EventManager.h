#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "src/event/Subscription.h"
#include "src/event/Event.h"

#define UNIVERSAL_EVENT_TAG -1 //get all events of specific ID, reguardless of tag

typedef unordered_map<int, std::list<Subscriber*>*> event_tag_map;
typedef std::list<Subscriber*> tag_sub_list;

class EventSubscriber;

class EventManager
{
public:

    void LaunchEvent(Event& e);

    void RegisterSubscriber(Subscriber* sub);

    bool EventExists(int event_id);
    bool TagExists(int event_id, tag_id);

    static EventManager* Instance()
    {
        static EventManager instance;
        return &instance;
    }

private:
    std::unordered_map<int, event_tag_map*> _subscription_registry;
    void AddSubscriberToSubscription(Subscriber* sub, int event_id, int event_tag);

};
#endif