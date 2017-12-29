#include "src/ui/RelativeLayout.h"

bool RelativeLayout::IsRelativeToLeftEdge(ptr<UIElement> child)
{
    auto descriptors = child->GetComponent("UI");
    return descriptors->GetStringValue("right_of").compare("LEFT_EDGE") == 0;
}

bool RelativeLayout::IsRelativeTopEdge(ptr<UIElement> child)
{
    auto descriptors = child->GetComponent("UI");
    return descriptors->GetStringValue("below").compare("TOP_EDGE") == 0;
}

void RelativeLayout::FormatRightOfEdge(int x_start, int y_start, ptr<UIElement> child)
{
    auto descriptors = child->GetComponent("UI");
    int x_rel = x_start + descriptors->GetFloatValue("margin_left");
    child->SetComponentValueFloat("Position", "x", x_rel);
}

void RelativeLayout::FormatBelowEdge(int x_start, int y_start, ptr<UIElement> child)
{
    auto descriptors = child->GetComponent("UI");
    int y_rel = y_start + descriptors->GetFloatValue("margin_top");
    child->SetComponentValueFloat("Position", "y", y_rel);
}

void RelativeLayout::FormatRight(ptr<UIElement> child, RelativeLayoutNode &parent_node)
{
    ptr<UIElement> parent = parent_node.parent;
    auto child_descriptors = child->GetComponent("UI");
    auto parent_descriptors = parent->GetComponent("UI");
    if (parent_node.right == nullptr)
    {
        int x_rel = parent->GetComponentValueFloat("Position", "x") +
                    parent->GetComponentValueFloat("Graphics", "width") +
                    parent_descriptors->GetFloatValue("margin_right") +
                    child_descriptors->GetFloatValue("margin_left");

        //int y_rel = parent->GetComponentValueFloat("Position", "y");

        child->SetComponentValueFloat("Position", "x", x_rel);
        //child->SetComponentValueFloat("Position", "y", y_rel);
    }
    else
    {
        throw InvalidFormatException("Right child is already set.");
    }
}

void RelativeLayout::FormatBelow(ptr<UIElement> child, RelativeLayoutNode &parent_node)
{
    ptr<UIElement> parent = parent_node.parent;
    auto child_descriptors = child->GetComponent("UI");
    auto parent_descriptors = parent->GetComponent("UI");
    if (parent_node.below == nullptr)
    {
        int y_rel = parent->GetComponentValueFloat("Position", "y") +
                    parent->GetComponentValueFloat("Graphics", "height") +
                    parent_descriptors->GetFloatValue("margin_bottom") +
                    child_descriptors->GetFloatValue("margin_top");

        //int x_rel = parent->GetComponentValueFloat("Position", "x");

        //child->SetComponentValueFloat("Position", "x", x_rel);
        child->SetComponentValueFloat("Position", "y", y_rel);
    }
    else
    {
        throw InvalidFormatException("Right child is already set.");
    }
}