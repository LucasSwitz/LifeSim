#ifndef SUBSCRIPTION
#define SUBSCRIPTION

#include <set>
#include <list>
#include "src/utils/lua/LuaUniversal.h"

/**
    Subscriptions are used by subscribers to describe the events they would like to listen
    to. An optional tags set can be set to listen to a specific subset of an event type. 
**/
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

    Subscription(int event_id, lua_State* state) : id(event_id) // should find a way to hide this
    {
        std::list<int> list;
        LuaUniversal::IntListFromLuaTable(list,state);

        for(auto it = list.begin(); it != list.end(); it++)
        {
            tags.insert(*it);
        }
    };

    int id;
    std::set<int> tags;
};

#endif