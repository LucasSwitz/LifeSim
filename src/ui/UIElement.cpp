#include "src/ui/UIElement.h"

UIElement::UIElement(int type_, std::string _name, int x, int y) : ComponentUser(ComponentUserType::CU_TYPE_UI_ELEMENT),
                                                                                type(type_),
                                                                                name(_name)
{
    SetPos(x, y);
}

void UIElement::SetPadding(int left, int right, int top, int bottom)
{
    padding = Padding(left, right, top, bottom);
}

void UIElement::SetDescriptor(const std::string k, const std::string value)
{
    descriptors[k] = value;
}

void UIElement::SetPos(int x, int y)
{
    SetX(x);
    SetY(y);
}

void UIElement::SetX(int x)
{
    AddComponentValue("Position", "x", (float)x);
}

void UIElement::SetY(int y)
{
    AddComponentValue("Position", "y", (float)y);
}

int UIElement::Type()
{
    return type;
}

void UIElement::Draw(PMIDGWindow &window)
{
    window.DrawComponentUser(this);
}

UIElement *UIElement::Clone()
{
    UIElement *e = new UIElement(type, name);
    return e;
}

std::string UIElement::Name()
{
    return name;
}

const std::unordered_map<std::string, std::string> &UIElement::GetDescriptors()
{
    return descriptors;
}