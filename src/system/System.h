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


   virtual void Update(double seconds_since_last_update) = 0;
   void OnEvent(Event& e) override{};
    std::list<Subscription> GetSubscriptions() override{
        std::list<Subscription> empty;
        return empty;
    };

  protected:
    System(std::string name = "") : _name(name){};
    std::string _name = "";
    std::string _after = "";
};

#endif