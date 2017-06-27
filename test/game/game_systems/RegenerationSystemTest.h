#ifndef HEALTHSYSTEMTEST_H
#define HEALTHSYSTEMTEST_H

#include <iostream>
#include "src/system/SystemFactory.h"
#include "src/system/SystemController.h"
#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/game_objects/LuaEntityFactory.h"

class RegenerationSystemTest : public LuaTest
{
  public:
    RegenerationSystemTest()
    {
        LuaEntityFactory::Instance()->PopulateFactory();
        SystemFactory::Instance()->PopulateFactory("",true);

    }
};

TEST_F(RegenerationSystemTest, TestRegeneration)
{
    Entity_Manager->Clear();
    SystemController::Instance()->AddToSystemExecutionSequence("RegenerationSystem");

    LuaEntity* e = LuaEntityFactory::Instance()->GetEntity("HealthTestEntity");

    ASSERT_EQ(e->GetComponentValueFloat("Health","hp"),12);

    e->SetComponentValueFloat("Health", "hp", 0);

    SystemController::Instance()->Update(3);
    
    ASSERT_EQ(10 ,e->GetComponentValueFloat("Health","hp"));

}
#endif
