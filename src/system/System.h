#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <chrono>

#include "src/event/EventSubscriber.h"

/**
    System are upated every game frame. They can also listen to events.
**/
class GameState;

template <typename T>
class System : public EventSubscriber
{
  public:
    const std::string& GetName() const
    {
        return _name;
    }
    
    std::string GetAfter() const
    {
        return _after;
    }

    double GetLastRuntime()
    {
        return _last_runtime;
    }

    double SetLastRuntime(float time)
    {
        _last_runtime = time;
    }

    void Pause()
    {
        _paused = true;
    }

    void Unpause()
    {
        _paused = false;
    }

    bool IsPaused()
    {
        return _paused;
    }

   virtual void Update(float seconds_since_last_update, T* g) = 0;
   
   void OnEvent(Event& e) override{};
    std::list<Subscription> GetSubscriptions() override{
        std::list<Subscription> empty;
        return empty;
    };

  protected:
    System(std::string name = "") : _name(name){};
    std::string _name = "";
    std::string _after = "";
    double _last_runtime = 0.0; //milliseconds
    bool _paused = false;
};

#endif