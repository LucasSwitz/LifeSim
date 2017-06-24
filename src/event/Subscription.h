#ifndef SUBSCRIPTION
#define SUBSCRIPTION

#include <set>
#include <list>
#include "src/utils/lua/LuaUniversal.h"

struct Subscription
{
    Subscription(int event_id) : id(event_id){};
    Subscription(int event_id, std::initializer_list<int> event_tags) : id(event_id)
    {
        for(auto it = event_tags.begin(); it != event_tags.end(); it++)
        {
            tags.insert(*it);
        }
    };

    Subscription(int event_id, LuaRef& event_tags) : id(event_id) // should find a way to hide this
    {
        std::list<int> list;

        LuaUniversal::ListFromTable<int>(event_tags,list);

        for(auto it = list.begin(); it != list.end(); it++)
        {
            tags.insert(*it);
        }
    };

    int id;
    std::set<int> tags;
};

#endif