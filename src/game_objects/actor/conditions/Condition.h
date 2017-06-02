#ifndef CONDITION_H
#define CONDITION_H

#include "src/game_objects/actor/Actor.h"

class Condition
{
    void virtual Start(Actor& t) = 0;
    void virtual Update(Actor& t) = 0;
    void virtual End(Actor& t) = 0;
    bool virtual isFinished(Actor& t) = 0;
};
#endif