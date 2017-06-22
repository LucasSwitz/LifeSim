#include "EventManager.h"
#include "src/event/EventSubscriber.h"


void EventManager::RegisterSubscriber(EventSubscriber* subscriber)
{
    std::list<Subscription> subscriptions = subscriber->GetSubscriptions();

    for(auto sub_it = subscriptions.begin(); sub_it != subscriptions.end(); sub_it++)
    {
        Subscription current_subscription = *sub_it;
        std::list<int> tags = current_subscription.tags;
        if(tags.empty())
            AddSubscriberToSubscription(subscriber, current_subscription.ID, UNIVERSAL_EVENT_TAG);
        for(auto tag_it = tags.begin(), tag_it != tags.end(); tag_it++)
        {
            int current_tag = *tag_it;
            AddSubscriberToSubscription(subscriber, current_subscription.ID, current_tag);
        }
    }
}

void EventManager::LaunchEvent(Event& e)
{
    //add universal subscribers
    e.tags.push_back(UNIVERSAL_EVENT_TAG);

    std::unordered_map<int, EventSubscriber*>* id_subscribers = _subscription_registry.at(e.ID);
    for(auto tag_it = e.tags.begin(); tag_it != e.tags.end(); tag_it++)
    {
        std::list<EventSubscriber*>* tag_subscribers_list = id_subscribers.at(*tag_it);
        for(auto it = tag_subscribers_list.begin(); it != tag_subscribers_list.end(); it++)
        {
            *it->OnEvent(e);
        }
    }

}

void EventManager::AddSubscriberToSubscription(EventSubscriber* sub, int event_id, int event_tag)
{
    event_tag_map* tag_map = nullptr;

    if(!EventExists(event_id))
    {
        _subscription_registry.insert(std::make_pair(event_id, new tag_map()))
    }

    tag_map = _subscription_registry.at(event_id);

    if(!TagExists(event_id, event_tag))
    {
        tag_map->insert(std::make_pair(event_tag,new tag_sub_list()));
    }

    tag_sub_list sub_list = tag_map->at(event_tag);
    sub_list->push_back(sub);
}

bool EventManager::EventExists(int event_id)
{
    return _subscription_registry.find(event_id) != _subscription_registry.end();
}

bool EventManager::TagExists(int event_id, int tag_id)
{
    if(!EventExists(event_id))
        return false;
    else
    {
        event_tag_map* tag_map = _subscription_registry.at(event_id);
        return tag_map->find(tag_id) != tag_map->end();
    } 
}