#ifndef CHARACTER_H
#define CHARACTER_H

#include "src/game_objects/actor/Actor.h"

class Character : public Actor
{

public:
    virtual void Tick();

    //this can be overriden to change a Character defaults (i.e state_machine).
    virtual void Init();
private:
    StateMachine<Character>* _state_machine;
};

#endif