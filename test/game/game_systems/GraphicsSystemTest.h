#ifndef GRAPHICSSYSTEMTEST_H
#define GRAPHICSSYSTEMTEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/component/ComponentUserBase.h"
#include "src/system/SystemController.h"
#include "src/gui/GameWindow.h"
#include <chrono>
#include <thread>

class GraphicsSystemTest : public LuaTest
{
    public:
        Entity* e_1;

        GraphicsSystemTest()
        {
            ComponentUserBase::Instance()->Reset();

            SystemFactory::Instance()->PopulateFactory();
            LuaEntityFactory::Instance()->PopulateFactory();

            e_1 = LuaEntityFactory::Instance()->GetEntity("GraphicsTestEntity");
            GameWindow::Instance()->Init();
        }
};

TEST_F(GraphicsSystemTest, TestSpriteLoad)
{

    GameWindow* game_window = GameWindow::NewInstance(); //create new window to draw
    game_window->Init();


    SystemController::Instance()->AddToSystemExecutionSequence("DrawGraphicsSystem");
    SystemController::Instance()->Update(0); //lua loads drawable components

    ASSERT_NO_FATAL_FAILURE(game_window->Update(0)); //updates engine graphics
    std::this_thread::sleep_for (std::chrono::seconds(2)); //time to view
    game_window->Shutdown();

}


#endif