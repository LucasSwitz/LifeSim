#include "src/game_objects/actor/character/Character.h"

Character::Character()
{   
     _state_machine = new ScriptableStateMachine<Character>(this);
}

void Character::Tick()
{
    _state_machine->Update();
    Actor::Tick();
}

void Character::Init()
{
      
}

ScriptableStateMachine<Character>* Character::GetStateMachine()
{
    return _state_machine;
}