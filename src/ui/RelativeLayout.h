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

    template<typename T>
    void Format(int x_start, int y_start, const T& elements)
    {
        int rel_x = x_start + _anchor_x;
        int rel_y = y_start + _anchor_y;

        for(ptr<UIElement> e : elements){
            auto descriptors = e->GetDescriptors();

            if(descriptors.find("right_of") != descriptors.end()){

            }else if (descriptors.find("below") != descriptrs.end()){
                
            }
            else{

            }
            
        }
    }

    private:
        int _anchor_x;
        int _anchor_y;
};

#endif