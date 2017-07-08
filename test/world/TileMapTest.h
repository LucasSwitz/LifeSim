#ifndef GAMERUNNERTEST_H
#define GAMERUNNERTEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include 
#include "test/game/GameRunnerTimed.h"

/**
    Depends on GraphicsSystem and SystemController
**/

class TileMapTest : public LuaTest
{
public:

    TileMap  tile_map;

    TilemapTest()
    {
        tile_map.LoadFromFile("path/to/tile/map");    
    }

    void SetUp()
    {
        
    }

    void TearDown()
    {
        
    }

};

TEST_F(TilemapTest, TestShowHideTileMap)
{
    tile_map.Show();
    SystemController::Instance()->AddToExecutionSequence("GraphicsSystem");
    SystemController::Instance()->Update(0);
    //sleep

    tile_map.Hide();
    //sleep
}


#endif
