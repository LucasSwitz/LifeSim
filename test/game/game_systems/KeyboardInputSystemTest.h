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

            e_1 = LuaEntityFactory::Instance()->GetEntity("MoveableGraphicsTestEntity");
        }

        void StartUp()
        {
            
        }
};

TEST_F(KeyboardInputSystemTest, MoveSpriteWithKeyboard)
{
    runner.Start();
    SystemController::Instance()->AddPassiveSystem("KeyboardInputSystem");
    SystemController::Instance()->AddToSystemExecutionSequence("DynamicsSystem");
    SystemController::Instance()->AddToSystemExecutionSequence("DrawGraphicsSystem");
    ASSERT_NO_FATAL_FAILURE(runner.RunTillClose());
}


#endif