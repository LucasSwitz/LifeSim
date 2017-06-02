#ifndef STARVED_H
#define STARVED_H

#include "src/game_objects/actor/conditions/Condition.h"

class Starved : public Condition
{
    Starved();
    void  Start(Actor& actor) override;
    void  Update(Actor& actor) override;
    void  End(Actor& actor) override;
    bool  isFinished(Actor& actor) override;
};

#endif