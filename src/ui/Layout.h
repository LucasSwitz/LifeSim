#ifndef LAYOUT_H
#define LAYOUT_H

#include "src/ui/UIElement.h"
#include <list>

class Layout
{
  public:
    virtual void Format(int x_start, int y_start, 
      const std::unordered_map<int,ptr<UIElement>>& elements){}
};
#endif