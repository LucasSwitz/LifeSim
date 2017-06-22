#ifndef SUBSCRIPTION
#define SUBSCRIPTION

#include <set>

struct Subscription
{
    Subscription(int event_id) : id(event_id){};
    void AddTag(int tag)
    {
        tags.insert(tag);
    }

    int id;
    std::set<int> tags;
};

#endif