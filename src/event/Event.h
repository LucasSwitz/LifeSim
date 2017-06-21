#ifndef EVENT_H
#define EVENT_H

#include <set>

struct Event
{
    int ID;
    int sender_id;
    int target_id; //make this set in the future maybe
    void* extra_info;

    template<typename T> 
    T DereferenceInfoToType()
    {
        reutrn *(T*)(extra_info);
    }
};

#endif