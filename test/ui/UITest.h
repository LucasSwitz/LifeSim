#ifndef UITEST_H
#define UITEST_H

#include "src/ui/BaseUI.h"
#include "test/lua_tests/lua_core/LuaTest.h"

class UITest : public LuaTest
{
  public:
    BaseUI *ui;
    UITest()
    {
    }

    void SetUp()
    {
        ui = new BaseUI(100, 100);
    }
};

TEST_F(UITest, TestRelativeLayoutLeft)
{
    ptr<UIElement> left = std::make_shared<UIElement>(0);
    left->AddComponentValue("Graphics", "width", 10.0f);
    left->AddComponentValue("Graphics", "height", 10.0f);
    left->SetDescriptor("right_of", "LEFT_EDGE");
    left->SetDescriptor("margin_left", "2");
    left->SetDescriptor("margin_right", "6");

    ptr<UIElement> right = std::make_shared<UIElement>(0);
    right->AddComponentValue("Graphics", "width", 10.0f);
    right->AddComponentValue("Graphics", "height", 10.0f);
    right->SetDescriptor("right_of", std::to_string(left->ID()));
    right->SetDescriptor("margin_left", "3");

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
    ptr<UIElement> top = std::make_shared<UIElement>(0);
    top->AddComponentValue("Graphics", "width", 10.0f);
    top->AddComponentValue("Graphics", "height", 10.0f);
    top->SetDescriptor("below", "TOP_EDGE");
    top->SetDescriptor("margin_bottom", "2");
    top->SetDescriptor("margin_top", "6");

    ptr<UIElement> bottom = std::make_shared<UIElement>(0);
    bottom->AddComponentValue("Graphics", "width", 10.0f);
    bottom->AddComponentValue("Graphics", "height", 10.0f);
    bottom->SetDescriptor("below", std::to_string(top->ID()));
    bottom->SetDescriptor("margin_top", "3");

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
