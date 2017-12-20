#ifndef LAYOUT_H
#define LAYOUT_H

#include "src/ui/UIElement.h"
#include <list>

class Layout
{
  public:
    enum Direction
    {
        RIGHT = 0,
        BELOW = 1
    };

    struct RelativePosition
    {
        RelativePosition(int parentID, Direction d) : parent(parentID), 
                                                      direction(d){}

        int parent;
        Direction direction;
    }

    virtual void Format(int x_start, int y_start, const std::list<UIElement *> &elements);
};

#endif