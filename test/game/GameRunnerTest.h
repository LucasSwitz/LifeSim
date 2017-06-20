#ifndef GAMERUNNERTEST_H
#define GAMERUNNERTEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include "test/game/GameRunnerTimed.h"

class GameRunnerTest : public LuaTest
{
public:

    GameRunnerTimed * runner;
    GameRunnerTest()
    {
        runner = new GameRunnerTimed();
    }

    void SetUp()
    {
        
    }

    void TearDown()
    {
        delete Entity_Manager->Instance();
    }

};

TEST_F(GameRunnerTest, TestTiming)
{
    Character* c = new Character();
    runner->RunFor(5);
}

#endif
