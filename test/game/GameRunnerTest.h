#ifndef GAMERUNNERTEST_H
#define GAMERUNNERTEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/game/GameRunner.h"

class GameRunnerTimed : public GameRunner
{
    public:
        void RunFor(double seconds)
        {
            auto start = std::chrono::high_resolution_clock::now();
            double duration = 0;
            while(duration < seconds)
            {
                this->Update();
                
                auto current_time = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - start).count();
            }

        }
};

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

};

TEST_F(GameRunnerTest, TestTiming)
{
    runner->RunFor(5);
}

#endif
