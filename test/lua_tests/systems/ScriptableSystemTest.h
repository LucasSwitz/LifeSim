#include <iostream>
#include "src/system/SystemController.h"
#include "test/lua_tests/lua_core/LuaTest.h"

class ScriptableSystemTest : public LuaTest
{
  public:
    ScriptableSystemTest()
    {
        SystemController::Instance()->PopulateFactory();
        SystemController::Instance()->Init();
    }

    void SetUp()
    {
    }
};

TEST_F(ScriptableSystemTest, TestOrderingMechanics)
{
    System *first = SystemController::Instance()->GetSystem("TestSystem1");
    System *second = SystemController::Instance()->GetSystem("TestSystem2");
    System *third = SystemController::Instance()->GetSystem("TestSystem3");

    EXPECT_TRUE(first == SystemController::Instance()->GetSystemInExecutionSequenceAt(0));
    EXPECT_TRUE(second == SystemController::Instance()->GetSystemInExecutionSequenceAt(1));
    EXPECT_TRUE(third == SystemController::Instance()->GetSystemInExecutionSequenceAt(2));
}
