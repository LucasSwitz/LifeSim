#ifndef LUABINDINGS_H
#define LUABINDINGS_H

#include <LuaBridge/LuaBridge.h>
#include "src/game_objects/actor/Actor.h"
#include "src/game_objects/actor/character/Character.h"
#include "src/utils/state/ScriptableStateMachine.h"
#include "src/game_objects/EntityManager.h"
#include "src/utils/lua/LuaList.h"
#include "src/event/Subscription.h"
#include "src/event/EventType.h"
#include "src/event/Event.h"
#include "src/decorator/Decorated.h"
#include "src/component/ComponentUserBase.h"

using namespace luabridge;

class LuaBindings
    {
    public:
        static void Bind(lua_State *L)
        { 
            getGlobalNamespace(L)
            .beginClass<Decorated>("Decorated")
                .addFunction("GetNumber", &Decorated::GetComponentValueFloat)
                .addFunction("SetNumber", &Decorated::SetComponentValueFloat)
            .endClass()
            .deriveClass<Entity, Decorated>("Entity")
                .addProperty("id", &Entity::ID)
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
            .endClass()
            .beginClass<LuaListNode<Entity>>("LuaListIterator")
                .addData("data",&LuaListNode<Entity>::data)
                .addData("next", &LuaListNode<Entity>::next)
            .endClass()
            .beginClass<LuaList<Entity>>("LuaList")
                .addFunction("Iterator", &LuaList<Entity>::Iterator)
            .endClass()
            .beginClass<EntityManager>("EntityManager")
                .addStaticFunction("Instance", &EntityManager::Instance)
                .addFunction("size", &EntityManager::GetNumberOfEntities)
                .addFunction("AsLuaList", &EntityManager::AsLuaList)
            .endClass()
            .beginClass<Component>("Component")
                .addFunction("GetNumber", &Component::GetFloatValue)
                .addFunction("GetString", &Component::GetStringValue)
                .addFunction("SetNumber", &Component::SetFloatValue)
                .addFunction("SetString", &Component::SetStringValue)
            .endClass()
            .beginClass<Subscription>("Subscription")
                .addConstructor<void (*)(int)>()
                .addFunction("AddTag", &Subscription::AddTag)
            .endClass()
            .beginClass<EventType>("EventType")
                .addStaticData("HEALTH_UPDATE_EVENT", &EventType::HEALTH_UPDATE_EVENT, false)
                .addStaticData("COLLISION_EVENT", &EventType::COLLISION_EVENT, false)
            .endClass()
            .beginClass<Event>("Event")
                .addData("type", &Event::id)
                .addData("sender", &Event::sender_id)
                .addData("target", &Event::target_id)
            .endClass()
            .beginClass<ComponentUserBase>("ComponentUsers")
                .addStaticFunction("Instance",&ComponentUserBase::Instance)
                .addFunction("GetAll",&ComponentUserBase::GetAllUsersWithComponentAsLuaList)
            .endClass();
        } 
 };

 #endif