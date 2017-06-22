#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <chrono>

#include "src/event/EventSubscriber.h"

class System : public EventSubscriber
{
  public:
    std::string GetName() const
    {
        return _name;
    }
    
    std::string GetAfter() const
    {
        return _after;
    }

    virtual void OnEvent(Event& e){};
    virtual std::list<Subscription> GetSubscriptions()
    {
        std::list empty();
        return empty; //might need to change this eventually
    }

   virtual void Update(double seconds_since_last_update) = 0;

  protected:
    System(std::string name = "") : _name(name){};
    std::string _name = "";
    std::string _after = "";
};

#endif