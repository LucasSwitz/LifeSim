#ifndef KEYBOARD_H
#define KEYBOARD_H

#include  <unordered_map>
#include "src/event/EventSubscriber.h"
#include "src/event/EngineEventManager.h"
#include "src/event/EventType.h"

/*
    The Keyboard is a convient global reference for all keyboard inputs. This class
    is not bound to any specific input handler, but is rather configured by input handlers launching
    key Events. 
*/

class Keyboard : public EventSubscriber
{
    public:
    Keyboard()
    {
        EngineEventManager::Instance()->RegisterSubscriber(this);
    }

    void OnEvent(Event& e)
    {
            if(e.id == EventType::W_DOWN_EVENT)
                SetKey('W',true);
            else if (e.id == EventType::A_DOWN_EVENT)
                SetKey('A',true);
            else if (e.id == EventType::S_DOWN_EVENT)
                SetKey('S',true);
            else if (e.id == EventType::D_DOWN_EVENT)
                SetKey('D',true);
            else if (e.id == EventType::E_DOWN_EVENT)
                SetKey('E',true);
            else if (e.id == EventType::W_UP_EVENT)
                SetKey('W',false);
            else if (e.id == EventType::A_UP_EVENT)
                SetKey('A',false);
            else if (e.id == EventType::S_UP_EVENT)
                SetKey('S',false);
            else if (e.id == EventType::D_UP_EVENT)
                SetKey('D',false);
            else if (e.id == EventType::E_UP_EVENT)
                SetKey('E',false);
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
    


    bool GetKey(char key)
    {
        if(ListeningToKey(key))
            return _keys.at(key);
        return false;
    }

    protected:
    
    void SetKey(char key, bool down)
    {
        if(!ListeningToKey(key))
            _keys.insert(std::make_pair(key,down));
        else
            _keys.find(key)->second = down;
    }

    bool ListeningToKey(char key)
    {
        return _keys.find(key) != _keys.end();
    }

    private:
        std::map<char, bool> _keys;

};                                                                      
#endif