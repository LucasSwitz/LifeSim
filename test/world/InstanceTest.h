#ifndef GAMERUNNERTEST_H
#define GAMERUNNERTEST_H

#include "test/lua_tests/lua_core/LuaTest.h"


class InstanceTest : public LuaTest
{
public:

    Instance*  instance;

    StageTest()
    {
        instance = LuaInstanceFactory::Instance()->GetInstance("TestInstance");   
    }

    void SetUp()
    {
        
    }

    void TearDown()
    {
        
    }

};

TEST_F(InstanceTest, TestInstanceLoad)
{
    instance->Load();
    ASSERT_EQ(DebugFlags::Instance()->Get("TestInstanceLoad"),"yes");
}

TEST_F(IntanceTest, TestInstanceUnload)
{
    instance->Unload();
    ASSERT_EQ(DebugFlags::Instance()->Get("TestInstanceUnload"),"yes");
}

TEST_F(IntanceTest, TestInstanceOpen)
{
    instance->Open();
    ASSERT_EQ(DebugFlags::Instance()->Get("TestInstanceOpen"),"yes");
}

TEST_F(IntanceTest, TestInstanceClose)
{
    instance->Close();
    ASSERT_EQ(DebugFlags::Instance()->Get("TestInstanceClose"),"yes");
}
#endif
