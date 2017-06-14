#ifndef CHARACTER_H
#define CHARACTER_H

#include "src/game_objects/actor/Actor.h"
#include "src/utils/state/ScriptableStateMachine.h"


class Character : public Actor
{

public:
    Character();
    virtual void Tick() override;

    //this can be overriden to change a Character defaults (i.e state_machine).
    virtual void Init();
    ScriptableStateMachine<Character>* GetStateMachine();
    
protected:
    ScriptableStateMachine<Character>* _state_machine;
};

#endif