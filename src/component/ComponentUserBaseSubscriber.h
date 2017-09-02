#ifndef COMPONENTUSERBASESUBSCRIBER_H
#define COMPONENTUSERBASESUBSCRIBER_H

#include "src/component/ComponentUserBaseEvent.h"

class ComponentUserBaseSubscriber
{
    public:
    virtual void OnEvent(ComponentUserBaseEvent& event) = 0;
};
#endif