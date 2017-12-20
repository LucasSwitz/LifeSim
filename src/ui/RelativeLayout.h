#ifndef RELATIVELAYOUT_H
#define RELATIVELAYOUT_H

#include "src/ui/Layout.h"

/*anchor is top left*/

class RelativeLayout : public Layout
{
  public:
    RelativeLayout(int anchor_x, int anchor_y) : _anchor_x (anchor_x),
                                                 _anchor_y (anchor_y)
    {

    }

    void Format(int x_start, int y_start, const std::list<UIElement *>& elements)
    {
        int rel_x = x_start + _anchor_x;
        int rel_y = y_start + _anchor_y;

        for(UIElement* e : elements)
        {
            
        }
    }

    private:
        int _anchor_x;
        int _anchor_y;
};

#endif