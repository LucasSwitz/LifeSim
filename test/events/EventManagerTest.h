#ifndef EVENTMANAGERTEST_H
#define EVENTMANAGERTEST_H

#include "src/event/EventManager.h"
#include "src/event/EventType.h"
#include <gtest/gtest.h>

class EventManagerTest : public EventSubscriber, public ::testing::Test
{
    public:
        bool event_recieved = false;
        EventManagerTest()
        {
            EventManager::Instance()->RegisterSubscriber(this);
        }

        void OnEvent(Event& e)
        {
            if(e.id == EventType::MAKE_THIS_EVENT_DURING_TEST)
                event_recieved = true;
        }

        std::list<Subscription> GetSubscriptions()
        {
            std::list<Subscription> subs;
            subs.push_back(Subscription(EventType::MAKE_THIS_EVENT_DURING_TEST));
            return subs;
        }
};

TEST_F(EventManagerTest, EventLoadNewEvent)
{
    ASSERT_FALSE(EventManager::Instance()->EventExists(EventType::NEVER_MAKE_THIS_EVENT));
    ASSERT_TRUE(EventManager::Instance()->EventExists(EventType::MAKE_THIS_EVENT_DURING_TEST));
}

TEST_F(EventManagerTest, TestEventLaunch)
{
    Event e(EventType::MAKE_THIS_EVENT_DURING_TEST,0,1);
    ASSERT_NO_FATAL_FAILURE(EventManager::Instance()->LaunchEvent(e));
    ASSERT_TRUE(event_recieved);
}

#endif