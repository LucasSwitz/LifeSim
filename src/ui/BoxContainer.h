#ifndef BOXCONTAINER_H
#define BOXCONTAINER_H

#include "src/ui/Container.h"

class BoxContainer : public Container
{
    public:
        BoxContainer(int x = 0, int y = 0, int width = 0, int height = 0) 
            : Container(x,y), width(0), height(0){}

    protected:
        int width;
        int height;
};
#endif