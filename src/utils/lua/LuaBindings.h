#ifndef LUABINDINGS_H
#define LUABINDINGS_H

#include <LuaBridge/LuaBridge.h>
#include "src/utils/state/ScriptableStateMachine.h"
#include "src/game_objects/EntityManager.h"
#include "src/utils/lua/LuaList.h"
#include "src/event/Subscription.h"
#include "src/event/EventType.h"
#include "src/event/Event.h"
#include "src/game_objects/LuaEntity.h"
#include "src/component/ComponentUserBase.h"
#include "src/component/ComponentUser.h"

using namespace luabridge;

class LuaBindings
    {
    public:
        static void Bind(lua_State *L)
        { 
            getGlobalNamespace(L)
            .beginClass<ComponentUser>("ComponentUser")
                .addFunction("GetNumber", &ComponentUser::GetComponentValueFloat)
                .addFunction("SetNumber", &ComponentUser::SetComponentValueFloat)
                .addFunction("GetString", &ComponentUser::GetComponentValueString)
                .addFunction("SetString", &ComponentUser::SetComponentValueString)
            .endClass()
            .deriveClass<Entity, ComponentUser>("Entity")
                .addProperty("id", &Entity::ID)
            .endClass()
            .deriveClass<LuaEntity, Entity>("LuaEntity")
                .addFunction("Add", &LuaEntity::AddComponent)
                .addFunction("Remove", &LuaEntity::RemoveComponent)
            .endClass()
            .beginClass<LuaListNode<ComponentUser*>>("LuaListIterator")
                .addData("data",&LuaListNode<ComponentUser*>::data)
                .addData("next", &LuaListNode<ComponentUser*>::next)
            .endClass()
            .beginClass<LuaList<ComponentUser*>>("LuaList")
                .addFunction("Iterator", &LuaList<ComponentUser*>::Iterator)
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