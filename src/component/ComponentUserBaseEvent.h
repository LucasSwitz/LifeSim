#ifndef COMPONENTUSERBASEEVENT_H
#define COMPONENTUSERBASEEVENT_H

#include "src/component/ComponentUser.h"

class ComponentUserBaseEvent
{
    public:
    enum Type
    {
        ADD,
        REMOVE
    };

    ComponentUserBaseEvent(Type event_type, ComponentUser* c_user, const std::string& name):
        type(event_type), user(c_user), component_name(name)
    {

    }

    Type type;
    ComponentUser* user = nullptr;
    std::string component_name;
};
#endif