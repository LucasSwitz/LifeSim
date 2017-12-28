#ifndef UITEST_H
#define UITEST_H

#include "src/ui/BaseUI.h"
#include <gtest/gtest.h>

class UITest : public ::testing::Test
{
  public:
    ptr<BaseUI> ui;
    UITest()
    {
    }

    void SetUp()
    {
        ui = std::make_shared<BaseUI>(100, 100);
    }
};

TEST_F(UITest, TestRelativeLayoutLeft)
{
    ptr<UIElement> left = std::make_shared<UIElement>(0,"left_test");
    left->AddComponentValue("Graphics", "width", 10.0f);
    left->AddComponentValue("Graphics", "height", 10.0f);
    left->AddComponentValue("UI", "right_of", (std::string)"LEFT_EDGE");
    left->AddComponentValue("UI", "margin_left", 2.0f);
    left->AddComponentValue("UI", "margin_right", 6.0f);

    ptr<UIElement> right = std::make_shared<UIElement>(0,"right_test");
    right->AddComponentValue("Graphics", "width", 10.0f);
    right->AddComponentValue("Graphics", "height", 10.0f);
    right->AddComponentValue("UI", "right_of", left->Name());
    right->AddComponentValue("UI", "margin_left", 3.f);

    ui->AddToRootContainer(ui->GetBaseContainerID(), left);
    ui->AddToRootContainer(ui->GetBaseContainerID(), right);

    ui->DoFormat();

    ASSERT_EQ(left->GetComponentValueFloat("Position", "x"), 2);
    ASSERT_EQ(left->GetComponentValueFloat("Position", "y"), 0);
    ASSERT_EQ(right->GetComponentValueFloat("Position", "y"), 0);
    ASSERT_EQ(right->GetComponentValueFloat("Position", "x"), left->GetComponentValueFloat("Position", "x") +
                                                                  left->GetComponentValueFloat("Graphics", "width") +
                                                                  3 +
                                                                  6);
}

TEST_F(UITest, TestRelativeLayoutTop)
{
    ptr<UIElement> top = std::make_shared<UIElement>(0,"top_test");
    top->AddComponentValue("Graphics", "width", 10.0f);
    top->AddComponentValue("Graphics", "height", 10.0f);
    top->AddComponentValue("UI", "below", (std::string)"TOP_EDGE");
    top->AddComponentValue("UI", "margin_bottom", 2.0f);
    top->AddComponentValue("UI", "margin_top", 6.0f);

    ptr<UIElement> bottom = std::make_shared<UIElement>(1,"bottom_test");
    bottom->AddComponentValue("Graphics", "width", 10.0f);
    bottom->AddComponentValue("Graphics", "height", 10.0f);
    bottom->AddComponentValue("UI", "below", top->Name());
    bottom->AddComponentValue("UI", "margin_top", 3.0f);

    ui->AddToRootContainer(ui->GetBaseContainerID(), top);
    ui->AddToRootContainer(ui->GetBaseContainerID(), bottom);

    ui->DoFormat();

    ASSERT_EQ(top->GetComponentValueFloat("Position", "x"), 0);
    ASSERT_EQ(top->GetComponentValueFloat("Position", "y"), 6);
    ASSERT_EQ(bottom->GetComponentValueFloat("Position", "x"), 0);
    ASSERT_EQ(bottom->GetComponentValueFloat("Position", "y"), top->GetComponentValueFloat("Position", "y") +
                                                                   top->GetComponentValueFloat("Graphics", "height") +
                                                                   2 +
                                                                   3);
}

#endif
