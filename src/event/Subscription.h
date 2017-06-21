#ifndef SUBSCRIPTION
#define SUBSCRIPTION

struct Subscritpion
{
    int event_id;
    std::set<int> _tags;
};

#endif