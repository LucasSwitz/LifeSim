#ifndef ENGINETEST_H
#define ENGINETEST_H

#include "src/engine/Engine.h"

#include <iostream>
#include <gtest/gtest.h>

class EngineTest : public ::testing::Test
{
  public:
    Engine e;
    EngineTest()
    {
        SystemFactory::Instance()->PopulateFactory(Globals::RESOURCE_ROOT);
    }
};

TEST_F(EngineTest, TestLoadJsonNonFatal)
{
    ASSERT_NO_FATAL_FAILURE(e.Load(Res("engine_conf.json")));
}

TEST_F(EngineTest, TestLoadJsonHasSystem)
{
    e.Load(Res("engine_conf.json"));
    ASSERT_TRUE(e.SystemIsRunning("DrawGraphicsSystem"));
    ASSERT_TRUE(e.SystemIsRunning("AnimationSystem"));
}
#endif
