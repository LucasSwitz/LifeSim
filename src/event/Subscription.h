#ifndef SUBSCRIPTION
#define SUBSCRIPTION

struct Subscritpion
{
    Subscription(int event_id);
    void AddTag(int tag)
    {
        _tags.insert(tag);
    }
    int event_id;
    std::set<int> _tags;
};

#endif