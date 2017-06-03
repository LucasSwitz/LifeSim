#ifndef GOAL_H
#define GOAL_H

#include <string>


class Actor;

class Goal{
public:
    Goal(std::string name) : _name(name){};
    virtual int Priority(Actor& actor) const = 0;
    virtual bool isFulfilled(Actor& actor) const = 0;
    virtual void Finish(Actor& actor) const {};
    virtual void Check(Actor& t) = 0;

    const std::string _name;
};
#endif