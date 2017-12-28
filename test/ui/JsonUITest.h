#ifndef JSONUITEST_H
#define JSONUITEST_H

#include "src/ui/UI.h"
#include <gtest/gtest.h>

class JsonUITest : public ::testing::Test
{
  public:
    UI ui;
    JsonUITest()
    {
    }

    void SetUp()
    {
    }
};

TEST_F(JsonUITest, TestNonFatalLoad)
{
    ASSERT_NO_FATAL_FAILURE(ui.Load(Res("TestUI.json")));
};

TEST_F(JsonUITest, TestUIHasComponents)
{
    ui.Load(Res("TestUI.json"));

    ASSERT_TRUE(ui.HasElement("TestContainer"));
    ASSERT_TRUE(ui.HasElement("TestGraphic"));
    ASSERT_TRUE(ui.HasRootElement("TestContainer"));
};

#endif
