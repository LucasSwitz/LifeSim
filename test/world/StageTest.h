#ifndef STAGETEST_H
#define STAGETEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/world/stage/Stage.h"
#include "src/world/stage/LuaStageFactory.h"

class StageTest : public LuaTest
{
public:

    Stage*  stage;

    StageTest()
    {
        LuaStageFactory::Instance()->PopulateFactory();
        stage = LuaStageFactory::Instance()->GetStage("TestStage");   
    }

    void SetUp()
    {
        
    }

    void TearDown()
    {
        
    }

};

TEST_F(StageTest, TestStageEnter)
{
    stage->Enter();
    ASSERT_EQ(DebugFlags::Instance()->Get("TestStageEnter"),"yes");
}

TEST_F(StageTest, TestStageExit)
{
    stage->Exit();
    ASSERT_EQ(DebugFlags::Instance()->Get("TestStageExit"), "yes");
}

TEST_F(StageTest, TestEnterRootInstance)
{
    stage->Enter();
    ASSERT_EQ(DebugFlags::Instance()->Get("TestInstanceLoad"), "yes");
    ASSERT_EQ(DebugFlags::Instance()->Get("TestInstanceOpen"), "yes");
}
#endif
