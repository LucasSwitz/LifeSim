#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <list>
#include <unordered_map>
#include <algorithm>
#include "src/event/Subscription.h"
#include "src/event/Event.h"
#include "src/event/EventSubscriber.h"

#define UNIVERSAL_EVENT_TAG -1 //get all events of specific ID, reguardless of tag

/**
    EventManager handles all launched events and relays them to the appropriate subscriber. 
    Subscribers are indexed first by the Event id and then by tags.
**/


typedef std::unordered_map<int, ptr<std::list<EventSubscriber*>>> event_tag_map;
typedef std::list<EventSubscriber*> tag_sub_list;
typedef std::unordered_map<int, ptr<event_tag_map>> subscription_registry;

class EventSubscriber;

class EventManager
{
    friend class GameState;
public:
    EventManager(): _subscription_registry() {}
    void LaunchEvent(Event& e);

    void RegisterSubscriber(EventSubscriber* sub);
    void Deregister(EventSubscriber* sub);
    void Deregister(EventSubscriber* sub, int event_id, int event_tag);

    bool EventExists(int event_id);
    bool TagExists(int event_id, int tag_id);

protected:
    void AddNewEvent(int event_id);
    void AddNewTag(int event_id, int tag);
    void AddSubscriberToSubscription(EventSubscriber* sub, int event_id, int event_tag);

private:
    subscription_registry _subscription_registry;

};
#endif