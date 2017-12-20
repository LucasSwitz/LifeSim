#ifndef CONTAINER_H
#define CONTAINER_H

#include <list>
#include "src/ui/Layout.h"

class Container : public UIElement
{
  public:
    Container(int x = 0, int y = 0) : UIElement(x, y)
    {

    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        if(_layout)
            _layout->Format(x_pos,y_pos,children);

        for (auto child : children)
        {
            target.draw(child, states);
        }
    }

    void setLayout(Layout *layout)
    {
        _layout = layout;
    }

  protected:
    std::list<UIElement *> children;

  private:
    Layout *_layout = nullptr;
};
#endif