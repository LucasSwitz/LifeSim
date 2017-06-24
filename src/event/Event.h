#ifndef EVENT_H
#define EVENT_H

#include <set>
#include "src/event/EventManager.h"

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