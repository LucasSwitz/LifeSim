#ifndef COMPONENT_USER_LISTENER_H
#define COMPONENT_USER_LISTENER_H

class ComponentUser;

class ComponentUserListener
{
public:
    virtual void OnDisableComponent (ComponentUser* user,const std::string& component_name){};
    virtual void OnEnableComponent(ComponentUser* user, const std::string component_name){};
};
#endif