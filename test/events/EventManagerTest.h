#ifndef EVENTMANAGERTEST_H
#define EVENTMANAGERTEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include "test/game/GameRunnerTimed.h"
#include "src/event/EventManager.h"
#include "src/event/EventType.h"
#include "src/system/ScriptableSystem.h"
class EventManagerTest : public LuaTest
{
    public:
        EventManagerTest()
        {
            SystemController::Instance()->PopulateFactory();
            SystemController::Instance()->Init();
        }
};

TEST_F(EventManagerTest, EventLoadNewEvent)
{
    System* s = SystemController::Instance()->GetSystem("HealthSystem");
    ASSERT_TRUE(s->HasEventHandling());
    ASSERT_TRUE(EventManager::Instance()->EventExists(EventType::HEALTH_UPDATE_EVENT));
    ASSERT_TRUE(EventManager::Instance()->EventExists(EventType::COLLISION_EVENT));
}

TEST_F(EventManagerTest, TestEventLaunch)
{
    Event e(EventType::HEALTH_UPDATE_EVENT,0,1);
    ASSERT_NO_FATAL_FAILURE(EventManager::Instance()->LaunchEvent(e));
}



#endif