#ifndef SCRIPTABLESYSTEMTEST_H
#define SCRIPTABLESYSTEMTEST_H

#include <iostream>
#include "src/system/SystemController.h"
#include "test/lua_tests/lua_core/LuaTest.h"

class ScriptableSystemTest : public LuaTest
{
  public:
    ScriptableSystemTest()
    {
        SystemFactory::Instance()->PopulateFactory();
    }

    void SetUp()
    {
        
    }
};

TEST_F(ScriptableSystemTest, TestOrderingMechanics)
{
    SystemController::Instance()->AddToSystemExecutionSequence("TestSystem1");
    SystemController::Instance()->AddToSystemExecutionSequence("TestSystem2");
    SystemController::Instance()->AddToSystemExecutionSequence("TestSystem3");

    EXPECT_TRUE(first == SystemController::Instance()->GetExecutionSequenceAt(0));
    EXPECT_TRUE(second == SystemController::Instance()->GetExecutionSequenceAt(1));
    EXPECT_TRUE(third == SystemController::Instance()->GetExecutionSequenceAt(2));
}
#endif
