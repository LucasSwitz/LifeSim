#include "src/ui/RelativeLayout.h"

RelativeLayout::RelativeLayout(int anchor_x, int anchor_y) : _anchor_x(anchor_x),
                                                             _anchor_y(anchor_y)
{
}

bool RelativeLayout::IsRelativeToLeftEdge(ptr<UIElement> child)
{
    auto descriptors = child->GetDescriptors();
    return descriptors["right_of"].compare("LEFT_EDGE") == 0;
}

bool RelativeLayout::IsRelativeTopEdge(ptr<UIElement> child)
{
    auto descriptors = child->GetDescriptors();
    return descriptors["below"].compare("TOP_EDGE") == 0;
}

void RelativeLayout::FormatRightOfEdge(ptr<UIElement> child)
{
    auto descriptors = child->GetDescriptors();
    int x_rel = std::stoi(descriptors["margin_left"]);
    child->SetComponentValueFloat("Position", "x", x_rel);
}

void RelativeLayout::FormatBelowEdge(ptr<UIElement> child)
{
    auto descriptors = child->GetDescriptors();
    int y_rel = std::stoi(descriptors["margin_top"]);

    child->SetComponentValueFloat("Position", "y", y_rel);
}

void RelativeLayout::FormatRight(ptr<UIElement> child, RelativeLayoutNode &parent_node)
{
    ptr<UIElement> parent = parent_node.parent;
    auto child_descriptors = child->GetDescriptors();
    auto parent_descriptors = parent->GetDescriptors();
    if (parent_node.right == nullptr)
    {
        int x_rel = parent->GetComponentValueFloat("Position", "x") +
                    parent->GetComponentValueFloat("Graphics", "width") +
                    std::stoi(parent_descriptors["margin_right"]) +
                    std::stoi(child_descriptors["margin_left"]);

        int y_rel = parent->GetComponentValueFloat("Position", "y");

        child->SetComponentValueFloat("Position", "x", x_rel);
        child->SetComponentValueFloat("Position", "y", y_rel);
    }
    else
    {
        throw InvalidFormatException("Right child is already set.");
    }
}

void RelativeLayout::FormatBelow(ptr<UIElement> child, RelativeLayoutNode &parent_node)
{
    ptr<UIElement> parent = parent_node.parent;
    auto child_descriptors = child->GetDescriptors();
    auto parent_descriptors = parent->GetDescriptors();
    if (parent_node.below == nullptr)
    {
        int y_rel = parent->GetComponentValueFloat("Position", "y") +
                    parent->GetComponentValueFloat("Graphics", "height") +
                    std::stoi(parent_descriptors["margin_bottom"]) +
                    std::stoi(child_descriptors["margin_top"]);

        int x_rel = parent->GetComponentValueFloat("Position", "x");

        child->SetComponentValueFloat("Position", "x", x_rel);
        child->SetComponentValueFloat("Position", "y", y_rel);
    }
    else
    {
        throw InvalidFormatException("Right child is already set.");
    }
}