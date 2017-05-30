#include "src/game_objectrs/actor/Goal.h"
class Need : public Goal
{
    
public:
    virtual void Check(Actor& t) = 0;
}