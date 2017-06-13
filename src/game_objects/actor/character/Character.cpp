#include "Character.h"


void Character::Tick()
{
    _state_machine->Update();
    Actor::Tick();
}

void Character::Init()
{
    _state_machine = new StateMachine<Character>(this);
}