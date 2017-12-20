#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <SFML/Graphics/Drawable.hpp>
#include "src/component/ComponentUser.h"

class UIElement : public sf::Drawable, public ComponentUser
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

    UIElement(int type_, std::string _name = "", int x = 0, int y = 0) : x_pos(x),
                                                                         y_pos(y),
                                                                         ComponentUser(ComponentUserType::CU_TYPE_UI_ELEMENT),
                                                                         type(type_),
                                                                         name(_name){}

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

    void SetPosition(int x, int y)
    {
        x_pos = x;
        y_pos = y;
    }

    void SetPadding(int left, int right, int top, int bottom)
    {
        padding = Padding(left, right, top, bottom);
    }

    void SetPos(int x, int y)
    {
        SetX(x);
        SetY(y);
    }

    void SetX(int x)
    {
        x_pos = x;
    }

    void SetY(int y)
    {
        y_pos = y;
    }

    int Type()
    {
        return type;
    }

    std::string Name()
    {
        return name;
    }

  protected:
    int x_pos;
    int y_pos;
    Padding padding;
    int id;
    int type;
    std::string name;
};
#endif