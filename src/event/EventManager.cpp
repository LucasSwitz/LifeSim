#include "EventManager.h"
#include "src/event/EventSubscriber.h"
#include <iostream>

void EventManager::RegisterSubscriber(EventSubscriber* subscriber)
{
    std::list<Subscription> subscriptions = subscriber->GetSubscriptions();
    for (auto sub_it = subscriptions.begin(); sub_it != subscriptions.end(); sub_it++)
    {
        Subscription current_subscription = *sub_it;
        std::set<int> tags = current_subscription.tags;
        if (tags.empty())
            AddSubscriberToSubscription(subscriber, current_subscription.id, UNIVERSAL_EVENT_TAG);
        for (auto tag_it = tags.begin(); tag_it != tags.end(); tag_it++)
        {
            int current_tag = *tag_it;
            AddSubscriberToSubscription(subscriber, current_subscription.id, current_tag);
        }
    }
}

void EventManager::LaunchEvent(Event &e)
{
    if (!EventExists(e.id))
    {
        AddNewEvent(e.id);
        return; //cause nobody cares
    }

    //add universal subscribers
    e.tags.insert(UNIVERSAL_EVENT_TAG);

    //add sender and reciever to tags
    e.tags.insert(e.sender_id);
    e.tags.insert(e.target_id);

    ptr<event_tag_map> id_subscribers = _subscription_registry.at(e.id);
    for (auto tag_it = e.tags.begin(); tag_it != e.tags.end(); tag_it++)
    {
        if (!TagExists(e.id, *tag_it))
        {
            AddNewTag(e.id, *tag_it);
            continue; //cause nobody cares
        }

        ptr<tag_sub_list> tag_subscribers_list = id_subscribers->at(*tag_it);
        for (auto it = tag_subscribers_list->begin(); it != tag_subscribers_list->end(); it++)
        {
                (*it)->OnEvent(e);
        }
    }
}

void EventManager::Deregister(EventSubscriber* subscriber)
{
    std::list<Subscription> subscriptions = subscriber->GetSubscriptions();
    for (auto sub_it = subscriptions.begin(); sub_it != subscriptions.end(); sub_it++)
    {
        Subscription current_subscription = *sub_it;
        std::set<int> tags = current_subscription.tags;
        tags.insert(UNIVERSAL_EVENT_TAG);
        if (tags.empty())
            Deregister(subscriber, current_subscription.id, UNIVERSAL_EVENT_TAG);
        for (auto tag_it = tags.begin(); tag_it != tags.end(); tag_it++)
        {
            int current_tag = *tag_it;
            Deregister(subscriber, current_subscription.id, current_tag);
        }
    }
}

void EventManager::Deregister(EventSubscriber* subscriber, int event_id, int event_tag)
{

    if (!EventExists(event_id) || !TagExists(event_id, event_tag))
    {
        return;
    }

    ptr<event_tag_map> tag_map = _subscription_registry.at(event_id);
    ptr<tag_sub_list> sub_list = tag_map->at(event_tag);
    auto subscriber_it = std::find(sub_list->begin(), sub_list->end(), subscriber);

    if (subscriber_it != sub_list->end())
    {
        sub_list->erase(subscriber_it);
    }
}

void EventManager::AddSubscriberToSubscription(EventSubscriber* sub, int event_id, int event_tag)
{
    if (!EventExists(event_id))
    {
        AddNewEvent(event_id);
    }

    if (!TagExists(event_id, event_tag))
    {
        AddNewTag(event_id, event_tag);
    }

    ptr<event_tag_map> tag_map = _subscription_registry.at(event_id);

    ptr<tag_sub_list> sub_list = tag_map->at(event_tag);

    sub_list->push_back(sub);
}

void EventManager::AddNewTag(int event_id, int tag)
{
    ptr<event_tag_map> tag_map = _subscription_registry.at(event_id);
    tag_map->insert(std::make_pair(tag, std::make_shared<tag_sub_list>()));
}

void EventManager::AddNewEvent(int event_id)
{
    _subscription_registry.insert(std::make_pair(event_id, std::make_shared<event_tag_map>()));   
}

bool EventManager::EventExists(int event_id)
{
    return _subscription_registry.find(event_id) != _subscription_registry.end();
}

bool EventManager::TagExists(int event_id, int tag_id)
{
    if (!EventExists(event_id))
        return false;
    else
    {
        ptr<event_tag_map> tag_map = _subscription_registry.at(event_id);
        return tag_map->find(tag_id) != tag_map->end();
    }
}