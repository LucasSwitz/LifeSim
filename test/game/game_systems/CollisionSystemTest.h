#ifndef COLLISIONSYSTEMTEST_H
#define COLLISIONSYSTEMTEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/event/EventSubscriber.h"
#include "src/component/ComponentUserBase.h"

class CollisionSystemTest : public LuaTest, public EventSubscriber
{
    public:
        Entity* e_1;
        Entity* e_2;

        bool _detected_collision = false;
        CollisionSystemTest()
        {
            ComponentUserBase::Instance()->Reset();
            SystemController::Instance()->PopulateFactory();
            LuaEntityFactory::Instance()->PopulateFactory();

            e_1 = LuaEntityFactory::Instance()->GetEntity("CollisionTestEntity1");
            e_2 = LuaEntityFactory::Instance()->GetEntity("CollisionTestEntity2");

            EventManager::Instance()->RegisterSubscriber(this);
        }

        void OnEvent(Event& e)
        {
            _detected_collision = true;
        }

        std::list<Subscription> GetSubscriptions()
        {
            std::list<Subscription> subs;
            subs.push_back(Subscription(EventType::COLLISION_EVENT, {e_1->ID(), e_2->ID()}));
            return subs;
        }
};

TEST_F(CollisionSystemTest, TestCollisionDetection)
{
    System* s = SystemController::Instance()->GetSystem("CollisionSystem");
    s->Update(0);
    ASSERT_TRUE(_detected_collision);
}


#endif