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

    void SetUp()
    {
        runner = new GameRunnerTimed();
    }

    void TearDown()
    {
        //delete runner;
    }
};

TEST_F(HealthSystemTest, TestRegeneration)
{
    Entity_Manager->Clear();
    LuaEntity* e = LuaEntityFactory::Instance()->GetEntity("HealthTestEntity");

    ASSERT_TRUE(e->HasComponent("Health"));

    e->GetComponent("Health")->SetFloatValue("hp",0);

    runner->RunFor(5);

    ASSERT_EQ(10 ,e->GetComponent("Health")->GetFloatValue("hp"));

}
#endif
