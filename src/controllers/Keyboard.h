#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include  <unordered_map>
#include "src/event/EventSubscriber.h"
#include "src/event/EngineEventManager.h"
class KeyboardController : public EventSubscriber
{
    public:
    const bool& Get(const std::string& key_name) const
    {
        return keys.at(key_name);
    }

    static KeyboardController* Instance()
    {
        static KeyboardController instance;
        return &instance;
    }

    void OnEvent(Event& e)
    {
            if(e.id == EventType::W_DOWN_EVENT)
                keys.find("W")->second = true;
            else if (e.id == EventType::A_DOWN_EVENT)
                keys.find("A")->second = true;
            else if (e.id == EventType::S_DOWN_EVENT)
                keys.find("S")->second = true;
            else if (e.id == EventType::D_DOWN_EVENT)
                keys.find("D")->second = true;
            else if (e.id == EventType::W_UP_EVENT)
                keys.find("W")->second = false;
            else if (e.id == EventType::A_UP_EVENT)
                keys.find("A")->second = false;
            else if (e.id == EventType::S_UP_EVENT)
                keys.find("S")->second = false;
            else if (e.id == EventType::D_UP_EVENT)
                keys.find("D")->second = false;
    }

    std::list<Subscription> GetSubscriptions()
    {
        std::list<Subscription> subs = {Subscription(EventType::W_DOWN_EVENT),
                                        Subscription(EventType::S_DOWN_EVENT),
                                        Subscription(EventType::A_DOWN_EVENT),
                                        Subscription(EventType::D_DOWN_EVENT),
                                        Subscription(EventType::W_UP_EVENT),
                                        Subscription(EventType::S_UP_EVENT),
                                        Subscription(EventType::A_UP_EVENT),
                                        Subscription(EventType::D_UP_EVENT)};

        return subs;
    }
    
    private:
    std::unordered_map<std::string, bool> keys = {{"W",false},
                                                  {"A",false},
                                                  {"S",false},
                                                  {"D",false}};

    KeyboardController()
    {
        EngineEventManager::Instance()->RegisterSubscriber(this);
    }

};                                                                      
#endif