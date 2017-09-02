#ifndef TIMEMAPTEST_H
#define TIMEMAPTEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/world/tile/LuaTileFactory.h"
#include "src/system/SystemController.h"
#include "src/world/tile/TileMap.h"
#include "src/gui/GameWindow.h"
#include <chrono>
#include <thread>

/**
    Depends on GraphicsSystem and SystemController
**/

class TileMapTest : public LuaTest
{
public:

    TileMap  tile_map;
    GameWindow* window;

    TileMapTest()
    {
        window = GameWindow::NewInstance();
        window->Init();

        LuaTileFactory::Instance()->PopulateFactory();
        SystemFactory::Instance()->PopulateFactory();
        SystemController::Instance()->Reset();
        tile_map.LoadFromFile("/home/lucas/Desktop/LifeSim/res/tile_maps/TestTileMap.txt");    
    }

    void SetUp()
    {
        
    }

    void TearDown()
    {
        
    }

};

TEST_F(TileMapTest, TestShowHideTileMap)
{
    tile_map.Show();
    SystemController::Instance()->AddToSystemExecutionSequence("DrawGraphicsSystem");

    SystemController::Instance()->Update(0);
    window->Update(0.0);
    //sleep
    std::this_thread::sleep_for(std::chrono::seconds(5));
    tile_map.Hide();

    window->Update(1.0);
    std::this_thread::sleep_for(std::chrono::seconds(5));


    //sleep
}


#endif
