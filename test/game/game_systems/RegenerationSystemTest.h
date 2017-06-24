#ifndef HEALTHSYSTEMTEST_H
#define HEALTHSYSTEMTEST_H

#include <iostream>
#include "test/game/GameRunnerTimed.h"
#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/game_objects/LuaEntityFactory.h"

class RegenerationSystemTest : public LuaTest
{
  public:
  GameRunnerTimed * runner;

    RegenerationSystemTest()
    {
        SystemController::Instance()->PopulateFactory();
        LuaEntityFactory::Instance()->PopulateFactory();
    }

    void SetUp()
    {

    }

    void TearDown()
    {
        //delete runner;
    }
};

TEST_F(RegenerationSystemTest, TestRegeneration)
{
    Entity_Manager->Clear();

    LuaEntity* e = LuaEntityFactory::Instance()->GetEntity("HealthTestEntity");

    ASSERT_EQ(e->GetComponentValueFloat("Health","hp"),12);

    e->SetComponentValueFloat("Health", "hp", 0);

    System* s = SystemController::Instance()->GetSystem("RegenerationSystem");
    s->Update(3);
    ASSERT_EQ(10 ,e->GetComponentValueFloat("Health","hp"));

}
#endif
