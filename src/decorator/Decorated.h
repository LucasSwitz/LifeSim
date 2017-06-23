#ifndef DECORATED_H
#define DECORATED_H

#include "src/decorator/EventHandlingDecorator.h"
#include "src/decorator/ComponentsDecorator.h"
#include "src/event/EventManager.h"
#include <iostream>
class Decorated
{
  public:
    bool HasEventHandling()
    {
        return _event_handler != nullptr;
    };

    bool HasComponentsDecorator()
    {
        return (_components_decorator != nullptr);
    }

    void AddEventHandling(EventHandlingDecorator *d)
    {
        _event_handler = d;
        EventManager::Instance()->RegisterSubscriber(_event_handler); //maybe change this to something more dynamic later;
    };

    void AddComponents(ComponentsDecorator *d)
    {
        _components_decorator = d;
    };

    void SetComponentValueFloat(std::string component_name, std::string value_name, float value)
    {
        if(HasComponentsDecorator())
            _components_decorator->GetComponent(component_name)->SetFloatValue(value_name,value);
    }

    float GetComponentValueFloat(std::string component_name, std::string value_name)
    {
        if(HasComponentsDecorator())
            return _components_decorator->GetComponent(component_name)->GetFloatValue(value_name);
        
        return -1; //throw error here
    }

    void SetComponentValueString(std::string component_name, std::string value_name, std::string value)
    {
        if(HasComponentsDecorator())
            _components_decorator->GetComponent(component_name)->SetStringValue(value_name,value);
    }

    std::string GetComponentValueString(std::string component_name, std::string value_name)
    {
        if(HasComponentsDecorator())
            return _components_decorator->GetComponent(component_name)->GetStringValue(value_name);
        
        return ""; //throw error here
    }

    bool HasComponent(std::string component_name)
    {
        if(!HasComponentsDecorator())
            return false;
        else
            return _components_decorator->HasComponent(component_name);
    }

  private:
    EventHandlingDecorator *_event_handler = nullptr;
    ComponentsDecorator *_components_decorator = nullptr;
};

#endif