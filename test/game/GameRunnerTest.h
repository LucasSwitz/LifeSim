#ifndef GAMERUNNERTEST_H
#define GAMERUNNERTEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include "test/game/GameRunnerTimed.h"
#include "src/system/SystemController.h"
#include "src/system/SystemFactory.h"
#include "src/component/ComponentUserBase.h"
#include "src/game_objects/LuaEntityFactory.h"

class GameRunnerTest : public LuaTest
{
public:

    GameRunnerTimed * runner;
    GameRunnerTest()
    {
        //ComponentUserBase::Instance()->Reset();
       // LuaEntityFactory::Instance()->PopulateFactory();

        SystemFactory::Instance()->PopulateFactory();
        runner = new GameRunnerTimed();
        runner->Start();
    }

    void SetUp()
    {
        
    }

    void TearDown()
    {
        
    }

};

TEST_F(GameRunnerTest, TestTiming)
{
    SystemController::Instance()->AddToSystemExecutionSequence("CollisionSystem");
    runner->RunFor(15);
}

#endif
