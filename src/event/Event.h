#ifndef EVENT_H
#define EVENT_H

#include <set>
#include "src/event/EventManager.h"

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
    void* extra_info;

    explicit Event(int event_id, int sender, int target, void* extra=nullptr) : 
                    id(event_id), sender_id(sender), target_id(target), extra_info(extra){};

    template<typename T> 
    T DereferenceInfoToType()
    {
        return *(T*)(extra_info);
    }

    int ExtraInfoAsInt()
    {
        return DereferenceInfoToType<int>();
    }

    
};

#endif