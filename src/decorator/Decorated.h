#ifndef DECORATED_H
#define DECORATED_H

#include "src/decorator/EventHandlingDecorator.h"
#include "src/decorator/ComponentsDecorator.h"
#include "src/event/EventManager.h"
class Decorated
{
  public:
    bool HasEventHandling()
    {
        return _event_handler != nullptr;
    };

    bool HasComponents()
    {
        return _components != nullptr;
    }

    void AddEventHandling(EventHandlingDecorator *d)
    {
        _event_handler = d;
        EventManager::Instance()->RegisterSubscriber(_event_handler); //maybe change this to something more dynamic later;
    };

    void AddComponents(ComponentsDecorator *d)
    {
        _components = d;
    };

    void SetComponentValueFloat(std::string component_name, std::string value_name, float value)
    {
        if(HasComponents())
            _components->GetComponent(component_name)->SetFloatValue(value_name,value);
    }

    float GetComponentValueFloat(std::string component_name, std::string value_name)
    {
        if(HasComponents())
            return _components->GetComponent(component_name)->GetFloatValue(value_name);
        
        return -1; //throw error here
    }

  private:
    EventHandlingDecorator *_event_handler = nullptr;
    ComponentsDecorator *_components = nullptr;
};

#endif