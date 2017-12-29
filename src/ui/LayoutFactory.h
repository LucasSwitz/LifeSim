#ifndef LAYOUTFACTORY_H
#define LAYOUTFACTORY_H

#include "src/ui/RelativeLayout.h"


class LayoutFactory
{
    public:
    ptr<Layout> Get(const std::string& name)
    {
        if(name.compare("Relative") == 0)
            return std::make_shared<RelativeLayout>();
    }
};

#endif