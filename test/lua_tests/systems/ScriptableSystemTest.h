#ifndef SCRIPTABLESYSTEMTEST_H
#define SCRIPTABLESYSTEMTEST_H

#include <iostream>
#include "src/system/SystemController.h"
#include "test/lua_tests/lua_core/LuaTest.h"

class ScriptableSystemTest : public LuaTest
{
  public:

    GameState g;
    ScriptableSystemTest()
    {
        SystemFactory::Instance()->PopulateFactory(Globals::RESOURCE_ROOT);
    }

    void SetUp()
    {
        
    }
};

TEST_F(ScriptableSystemTest, TestOrderingMechanics)
{
    System* first = SystemFactory::Instance()->GetSystem("TestSystem1");
    System* second = SystemFactory::Instance()->GetSystem("TestSystem2");
    System* third = SystemFactory::Instance()->GetSystem("TestSystem3");

    g.AddSystem(first);
    g.AddSystem(second);
    g.AddSystem(third);

    EXPECT_TRUE(first == g.GetSystemController().GetExecutionSequenceAt(0));
    EXPECT_TRUE(second == g.GetSystemController().GetExecutionSequenceAt(1));
    EXPECT_TRUE(third == g.GetSystemController().GetExecutionSequenceAt(2));
}
#endif
