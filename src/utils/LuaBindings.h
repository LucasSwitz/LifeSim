#ifndef LUABINDINGS_H
#define LUABINDINGS_H

#include <LuaBridge/LuaBridge.h>
#include "src/game_objects/actor/Actor.h"
#include "src/game_objects/actor/character/Character.h"
#include "src/utils/state/ScriptableStateMachine.h"


using namespace luabridge;

class LuaBindings
    {
    public:
        static void Bind(lua_State *L)
        { 
            getGlobalNamespace(L)
            .beginClass<Entity>("Entity")
            .endClass()
            .deriveClass<Actor, Entity>("Actor")
                .addConstructor<void(*)(void)>()
                .addFunction("SetInternalValue", &Actor::SetInternalValue)
                .addFunction("GetInternalValue", &Actor::GetInternalValue)
            .endClass()
            .deriveClass<Character,Actor>("Character")
            .addFunction("GetStateMachine", &Character::GetStateMachine)
            .endClass()
            .beginClass<ScriptableStateMachine<Character>>("ScriptableStateMachine")
                .addFunction("ChangeState",&ScriptableStateMachine<Character>::ChangeState)
            .endClass();
        } 
 };

 #endif