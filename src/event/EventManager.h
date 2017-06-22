#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <list>
#include <unordered_map>
#include "src/event/Subscription.h"
#include "src/event/Event.h"
#include "src/event/EventSubscriber.h"

#define UNIVERSAL_EVENT_TAG -1 //get all events of specific ID, reguardless of tag

typedef std::unordered_map<int, std::list<EventSubscriber*>*> event_tag_map;
typedef std::list<EventSubscriber*> tag_sub_list;

class EventSubscriber;

class EventManager
{
public:

    void LaunchEvent(Event& e);

    void RegisterSubscriber(EventSubscriber* sub);

    bool EventExists(int event_id);
    bool TagExists(int event_id, int tag_id);

    static EventManager* Instance()
    {
        static EventManager instance;
        return &instance;
    }

protected:
    void AddNewEvent(int event_id);
    void AddNewTag(int event_id, int tag);
    void AddSubscriberToSubscription(EventSubscriber* sub, int event_id, int event_tag);

private:
    std::unordered_map<int, event_tag_map*> _subscription_registry;

};
#endif