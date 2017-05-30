#ifndef GOAL_H
#define GOAL_H

#include <string>
#include "src/game_objects/actor/Actor.h"

class Goal{
public:
    Goal(std::string name);
    virtual int Priority(Actor& actor) const = 0;
    virtual bool isFulfilled(Actor& actor) const = 0;
    virtual void Finish(Actor& actor) const {};

    const std::string _name;
};
#endif