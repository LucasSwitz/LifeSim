#ifndef SCRIPTABLESYSTEMTEST_H
#define SCRIPTABLESYSTEMTEST_H

#include <iostream>
#include "test/lua_tests/lua_core/LuaTest.h"


class ScriptableSystemTest : public LuaTest
{
  public:
    ptr<GameState> g;
    ScriptableSystemTest()
    {
        g = std::make_shared<GameState>();
        SystemFactory::Instance()->PopulateFactory(Globals::RESOURCE_ROOT);
    }
};

TEST_F(ScriptableSystemTest, TestOrderingMechanics)
{
    ptr<game_system> first = ptr<game_system>(SystemFactory::Instance()->GetSystem<GameState>("TestSystem1"));
    ptr<game_system> second = ptr<game_system>(SystemFactory::Instance()->GetSystem<GameState>("TestSystem2"));
    ptr<game_system> third = ptr<game_system>(SystemFactory::Instance()->GetSystem<GameState>("TestSystem3"));

    g->AddSystem(first);
    g->AddSystem(second);
    g->AddSystem(third);

    EXPECT_TRUE(first == g->GetSystemController().GetExecutionSequenceAt(0));
    EXPECT_TRUE(second == g->GetSystemController().GetExecutionSequenceAt(1));
    EXPECT_TRUE(third == g->GetSystemController().GetExecutionSequenceAt(2));
}
#endif
