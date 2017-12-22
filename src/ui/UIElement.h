#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <SFML/Graphics/Drawable.hpp>
#include "src/component/ComponentUser.h"
#include "src/ui/UIElementTypes.h"
#include "src/graphics/gui/PMIDGWindow.h"

class UIElement : public ComponentUser, public sf::Drawable
{
  public:
    struct Padding
    {

        Padding(int _left = 0, int _right = 0, int _top = 0, int _bottom = 0) : left(_left),
                                                                                right(_right),
                                                                                top(_top),
                                                                                bottom(_bottom){};
        int left;
        int right;
        int top;
        int bottom;
    };

    UIElement(int type_, std::string _name = "", int x = 0, int y = 0) : ComponentUser(ComponentUserType::CU_TYPE_UI_ELEMENT),
                                                                         type(type_),
                                                                         name(_name)
    {
        SetPos(x, y);
    }

    void SetPadding(int left, int right, int top, int bottom)
    {
        padding = Padding(left, right, top, bottom);
    }

    void SetDescriptor(const std::string k, const std::string value)
    {
        descriptors[k] = value;
    }

    void SetPos(int x, int y)
    {
        SetX(x);
        SetY(y);
    }

    void SetX(int x)
    {
        AddComponentValue("Position", "x", (float)x);
    }

    void SetY(int y)
    {
        AddComponentValue("Position", "y", (float)y);
    }

    int Type()
    {
        return type;
    }

    virtual void Draw(PMIDGWindow& window)
    {
        window.DrawComponentUser(this);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates s) const
    {

    }

    UIElement *Clone()
    {
        UIElement *e = new UIElement(type, name);
        return e;
    }

    std::string Name()
    {
        return name;
    }

    const std::unordered_map<std::string,std::string>& GetDescriptors()
    {
        return descriptors;
    }

  protected:
    Padding padding;
    int id;
    int type;
    std::string name;
    std::unordered_map<std::string, std::string> descriptors;
};
#endif