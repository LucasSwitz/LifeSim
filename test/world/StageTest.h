#ifndef GAMERUNNERTEST_H
#define GAMERUNNERTEST_H

#include "test/lua_tests/lua_core/LuaTest.h"


class StageTest : public LuaTest
{
public:

    Stage*  stage;

    StageTest()
    {
        stage = LuaStageFactory::Instance()->GetInstance("TestStage");   
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
