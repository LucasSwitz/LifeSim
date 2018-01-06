#ifndef COMPONENT_USER_LISTENER_H
#define COMPONENT_USER_LISTENER_H

class ComponentUser;

class ComponentUserListener
{
public:
    virtual void OnDisableComponent (ptr<ComponentUser> user,const std::string& component_name) = 0;
    virtual void OnEnableComponent(ptr<ComponentUser> user, const std::string& component_name) = 0;
};
#endif