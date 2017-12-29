#ifndef COLLISIONSYSTEMTEST_H
#define COLLISIONSYSTEMTEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/event/EventSubscriber.h"
#include "src/component/ComponentUserBase.h"
#include "src/system/SystemController.h"
#include "src/event/EventManager.h"

class CollisionSystemTest : public LuaTest, public EventSubscriber
{
  public:
    bool _detected_collision = false;
    ptr<GameState> g;
    ptr<Entity> e1;
    ptr<Entity> e2;
    ComponentUserBase cub;

    CollisionSystemTest()
    {
        g = std::make_shared<GameState>();

        SystemFactory::Instance()->PopulateFactory(Globals::RESOURCE_ROOT);
        LuaEntityFactory::Instance()->PopulateFactory(Globals::RESOURCE_ROOT);
        LuaTileFactory::Instance()->PopulateFactory(Globals::RESOURCE_ROOT);

        TileMap t;
        t.LoadFromFile(Res(".pmidgM"));

        ptr<Instance> i = ptr<Instance>(new Instance(-2, "TestCollisionInstance"));
        
        i->SetTileMap(t);
        ptr<Stage> s = ptr<Stage>(new Stage(cub));

        s->AddInstance(i);
        s->SetRootInstance(i);
        s->SetCurrentInstance(i->GetID(), true);

        e1 = ptr<Entity>(LuaEntityFactory::Instance()->GetEntityByName("CollisionTestEntity1"));
        e2 = ptr<Entity>(LuaEntityFactory::Instance()->GetEntityByName("CollisionTestEntity2"));

        e1->SetInstance(i->GetID());
        e2->SetInstance(i->GetID());

        g->SetStage(s);

        g->AddEntity(e1);
        g->AddEntity(e2);

        g->GetMessageDispatch().RegisterSubscriber(this);
    }

    void OnEvent(Event &e)
    {
        _detected_collision = true;
    }

    std::list<Subscription> GetSubscriptions()
    {
        std::list<Subscription> subs;
        subs.push_back(Subscription(EventType::COLLISION_EVENT, {e1->ID(), e2->ID()}));
        return subs;
    }
};

TEST_F(CollisionSystemTest, TestCollisionDetection)
{
    g->AddSystem("CollisionSystem");
    g->Tick(1.0);
    ASSERT_TRUE(_detected_collision);
}

#endif