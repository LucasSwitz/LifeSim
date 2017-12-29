#include "src/ui/UIElement.h"

UIElement::UIElement(int type_, std::string _name, int x, int y) : ComponentUser(CU_TYPE_UI_ELEMENT),
                                                                   type(type_),
                                                                   name(_name)
{
    SetPos(x, y);
}

void UIElement::SetPadding(int left, int right, int top, int bottom)
{
    padding = Padding(left, right, top, bottom);
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

void UIElement::Draw(TBWindow &window)
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

using json = nlohmann::json;
ptr<UIElement> UIElement::FromJson(int type, const json &json)
{
    ptr<UIElement> el = std::make_shared<UIElement>(type);
    FromJson(el, json);
    return el;
}

void UIElement::FromJson(ptr<UIElement> el, const nlohmann::json &json)
{
    ComponentUser::FromJson(el, json);
    el->name = json["name"];
}

void UIElement::Show()
{
    EnableAll();
}

void UIElement::Hide()
{
    DisableAll();
}