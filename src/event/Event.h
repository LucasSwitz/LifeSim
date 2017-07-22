#ifndef EVENT_H
#define EVENT_H

#include <set>
#include "src/component/ComponentUser.h"

/** 
    Events can be launched from anywhere in the code. The launched event is then processed
    by the EventManager and handled by EventSubscribers. Every event as a void* extra_info 
    field that can be filled with any data then dereferenced to its desired type.
**/

struct Event
{
    int id;
    int sender_id;
    int target_id; 
    std::set<int> tags; //maybe use this in the furture
    void* extra_info = nullptr;

    Event(){};
    explicit Event(int event_id, int sender, int target, void* extra=nullptr) : 
                    id(event_id), sender_id(sender), target_id(target), extra_info(extra)
    {

    };

    template<typename T>
    static Event Create(int event_id, int sender, int target, T* data)
    {
        Event e;
        e.id = event_id;
        e.sender_id = sender;
        e.target_id = target;
        e.extra_info = static_cast<void*>(data);

        return e;
    }

    template<typename T> 
    T InfoToType()
    {
        return (T)(extra_info);
    }
};

#endif