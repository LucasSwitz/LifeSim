#ifndef GAMESYSTEMLOADTEST_H
#define GAMESYSTEMLOADTEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/event/EventSubscriber.h"
#include "src/component/ComponentUserBase.h"
#include "src/system/SystemController.h"
#include "src/event/EventManager.h"

class GameSystemLoadTest : public LuaTest
{
  public:
    ptr<GameState> g;
    ptr<Entity> e1;
    ptr<Entity> e2;
    ComponentUserBase cub;

    GameSystemLoadTest()
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
    }
};

TEST_F(GameSystemLoadTest, TestCollisionLoad)
{
    g->AddSystem("CollisionSystem");
    ASSERT_NO_FATAL_FAILURE(g->Tick(1.0););
}

TEST_F(GameSystemLoadTest, TestGraphicsSystemLoad)
{
    g->AddSystem("DrawGraphicsSystem");
    ASSERT_NO_FATAL_FAILURE(g->Tick(1.0););
}

TEST_F(GameSystemLoadTest, TestAnimationSystemLoad)
{
    g->AddSystem("AnimationSystem");
    ASSERT_NO_FATAL_FAILURE(g->Tick(1.0););
}

TEST_F(GameSystemLoadTest, TestDynamicsSystemLoad)
{
    g->AddSystem("DynamicsSystem");
    ASSERT_NO_FATAL_FAILURE(g->Tick(1.0););
}

TEST_F(GameSystemLoadTest, TestGravitySystemLoad)
{
    g->AddSystem("GravitySystem");
    ASSERT_NO_FATAL_FAILURE(g->Tick(1.0););
}

TEST_F(GameSystemLoadTest, TestStateSystemLoad)
{
    g->AddSystem("StateSystem");
    ASSERT_NO_FATAL_FAILURE(g->Tick(1.0););
}

TEST_F(GameSystemLoadTest, TestSystemLoadFail)
{
    ASSERT_THROW(g->AddSystem("FakeSystem"),AssetNotFoundException);
}

#endif