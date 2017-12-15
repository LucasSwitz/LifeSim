#ifndef INSTANCETEST_H
#define INSTANCETEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/world/stage/Instance.h"
#include "src/world/stage/LuaInstanceFactory.h"

class InstanceTest : public LuaTest
{
public:

    Instance* instance;
    EntityManager em;

    InstanceTest()
    {
        LuaInstanceFactory::Inst()->PopulateFactory(Globals::RESOURCE_ROOT);
        instance = LuaInstanceFactory::Inst()->GetInstance("TestInstance");   
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

TEST_F(InstanceTest, TestInstanceUnload)
{
    instance->Unload();
    ASSERT_EQ(DebugFlags::Instance()->Get("TestInstanceUnload"),"yes");
}

TEST_F(InstanceTest, TestInstanceOpen)
{
    instance->Load();
    instance->Open(em);
    ASSERT_EQ(DebugFlags::Instance()->Get("TestInstanceOpen"),"yes");
}

TEST_F(InstanceTest, TestInstanceClose)
{
    instance->Close(em);
    ASSERT_EQ(DebugFlags::Instance()->Get("TestInstanceClose"),"yes");
}
#endif
