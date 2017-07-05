#ifndef KEYBOARDINPUTSYSTEMTEST_H
#define KEYBOARDINPUTSYSTEMTEST_H

#include "src/game_objects/LuaEntityFactory.h"
#include "src/component/ComponentUserBase.h"
#include "src/system/SystemController.h"
#include "src/gui/GameWindow.h"
#include "test/game/GameRunnerTimed.h"
#include "test/lua_tests/lua_core/LuaTest.h"
#include <chrono>
#include <thread>

class KeyboardInputSystemTest : public LuaTest
{
    public:
        Entity* e_1;
        GameRunnerTimed runner;

        KeyboardInputSystemTest() : runner()
        {
            ComponentUserBase::Instance()->Reset();
            EntityManager::Instance()->Clear();

            SystemFactory::Instance()->PopulateFactory();
            LuaEntityFactory::Instance()->PopulateFactory();

            e_1 = LuaEntityFactory::Instance()->GetEntity("TestEntity");
        }

        void StartUp()
        {
            
        }
};

TEST_F(KeyboardInputSystemTest, MoveSpriteWithKeyboard)
{
    runner.Start();
    SystemController::Instance()->AddToSystemExecutionSequence("StateSystem");
    SystemController::Instance()->AddToSystemExecutionSequence("DynamicsSystem");
    SystemController::Instance()->AddToSystemExecutionSequence("DrawGraphicsSystem");
    SystemController::Instance()->AddToSystemExecutionSequence("AnimationSystem");
    ASSERT_NO_FATAL_FAILURE(runner.RunTillClose());
}


#endif