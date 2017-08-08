#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include  <unordered_map>
#include "src/event/EventSubscriber.h"
#include "src/event/EngineEventManager.h"
#include "src/event/EventType.h"
#include "src/controllers/IODevice.h"

/*
    The Keyboard controller is a convient global reference for all keyboard inputs. This class
    is not bound to any specific input handler, but is rather configured by input handlers launching
    key Events. 
*/

#define W_KEY_TRIGGER 0
#define A_KEY_TRIGGER 1
#define S_KEY_TRIGGER 2
#define D_KEY_TRIGGER 3
#define E_KEY_TRIGGER 4

class KeyboardController : public IODevice, public EventSubscriber
{
    public:

    static int W_S_TRIGGER;
    static int A_S_TRIGGER;
    static int S_S_TRIGGER;
    static int D_S_TRIGGER;
    static int E_S_TRIGGER;

    void Poll(){};

    static KeyboardController* Instance()
    {
        static KeyboardController instance;
        return &instance;
    }

    void OnEvent(Event& e)
    {
            if(e.id == EventType::W_DOWN_EVENT)
                Set(W_KEY_TRIGGER,true);
            else if (e.id == EventType::A_DOWN_EVENT)
                Set(A_KEY_TRIGGER,true);
            else if (e.id == EventType::S_DOWN_EVENT)
                Set(S_KEY_TRIGGER,true);
            else if (e.id == EventType::D_DOWN_EVENT)
                Set(D_KEY_TRIGGER,true);
            else if (e.id == EventType::E_DOWN_EVENT)
                Set(E_KEY_TRIGGER,true);
            else if (e.id == EventType::W_UP_EVENT)
                Set(W_KEY_TRIGGER,false);
            else if (e.id == EventType::A_UP_EVENT)
                Set(A_KEY_TRIGGER,false);
            else if (e.id == EventType::S_UP_EVENT)
                Set(S_KEY_TRIGGER,false);
            else if (e.id == EventType::D_UP_EVENT)
                Set(D_KEY_TRIGGER,false);
            else if (e.id == EventType::E_UP_EVENT)
                Set(E_KEY_TRIGGER,false);
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
                                        Subscription(EventType::D_UP_EVENT),
                                        Subscription(EventType::E_DOWN_EVENT),
                                        Subscription(EventType::E_UP_EVENT)};

        return subs;
    }
    
    KeyboardController()
    {
        EngineEventManager::Instance()->RegisterSubscriber(this);
    }

};                                                                      
#endif