#ifndef HEALTHSYSTEMTEST_H
#define HEALTHSYSTEMTEST_H

#include <iostream>
#include "test/game/GameRunnerTimed.h"
#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/game_objects/LuaEntityFactory.h"

class HealthSystemTest : public LuaTest
{
  public:
  GameRunnerTimed * runner;

    HealthSystemTest()
    {
        SystemController::Instance()->PopulateFactory();
        LuaEntityFactory::Instance()->PopulateFactory();
    }

    void SetUp()
    {
        runner = new GameRunnerTimed(); //GameRunner initialized SystemController
    }

    void TearDown()
    {
        //delete runner;
    }
};

TEST_F(HealthSystemTest, TestRegeneration)
{
    Entity_Manager->Clear();
    Entity* e = LuaEntityFactory::Instance()->GetEntity("HealthTestEntity");

    ASSERT_EQ(e->GetComponentValueFloat("Health","hp"),12);

    e->SetComponentValueFloat("Health", "hp", 0);

    runner->RunFor(5);

    ASSERT_EQ(10 ,e->GetComponentValueFloat("Health","hp"));

}
#endif
