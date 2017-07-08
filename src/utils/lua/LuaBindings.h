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
#include "src/gui/GameWindow.h"
#include "src/controllers/Keyboard.h"
#include "src/world/tile/Tile.h"
#include "src/world/stage/Stage.h"
#include "src/world/stage/Instance.h"
#include "src/utils/debug/DebugFlags.h"
#include "src/world/stage/LuaInstance.h"
#include "src/world/stage/LuaStage.h"

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
                .addFunction("SetBool", &ComponentUser::SetComponentBoolValue)
                .addFunction("GetBool", &ComponentUser::GetComponentBoolValue)
                .addFunction("GetComponent", &ComponentUser::GetComponent)
            .endClass()
            .deriveClass<Entity, ComponentUser>("Entity")
                .addProperty("id", &Entity::ID)
                .addFunction("IsType", &Entity::IsType)
                .addFunction("Call", &Entity::CallFunction)
                .addStaticData("CPP_DEFINED_ENTITY", &Entity::CPP_DEFINED_ENTITY)
                .addStaticData("LUA_DEFINED_ENTITY", &Entity::LUA_DEFINED_ENTITY)
            .endClass()
            .deriveClass<LuaEntity, Entity>("LuaEntity")
                .addStaticFunction("Downcast",&LuaEntity::DownCastFromEntity)
                .addFunction("Add", &LuaEntity::AddComponent)
                .addFunction("Remove", &LuaEntity::RemoveComponent)
                .addFunction("AsTable",&LuaEntity::AsTable)
                .addFunction("Call",&LuaEntity::CallFunction)
                .addFunction("SetNumberL", &LuaEntity::SetNumber)
            .endClass()
            .beginClass<LuaListNode<ComponentUser*>>("LuaListComponentUserIterator")
                .addData("data",&LuaListNode<ComponentUser*>::data)
                .addData("next", &LuaListNode<ComponentUser*>::next)
            .endClass()
            .beginClass<LuaListNode<Entity*>>("LuaListEntityIterator")
                .addData("data",&LuaListNode<Entity*>::data)
                .addData("next", &LuaListNode<Entity*>::next)
            .endClass()
            .beginClass<LuaList<ComponentUser*>>("LuaListComponentUser")
                .addFunction("Iterator", &LuaList<ComponentUser*>::Iterator)
            .endClass()
            .beginClass<LuaList<Entity*>>("LuaListEntity")
                .addFunction("Iterator", &LuaList<Entity*>::Iterator)
            .endClass()
            .beginClass<EntityManager>("EntityManager")
                .addStaticFunction("Instance", &EntityManager::Instance)
                .addFunction("size", &EntityManager::GetNumberOfEntities)
                .addFunction("Get", &EntityManager::GetEntityByID)
                .addFunction("AsLuaList", &EntityManager::AsLuaList)
            .endClass()
            .beginClass<Component>("Component")
                .addFunction("GetNumber", &Component::GetFloatValue)
                .addFunction("GetString", &Component::GetStringValue)
                .addFunction("SetNumber", &Component::SetFloatValue)
                .addFunction("SetString", &Component::SetStringValue)
                .addFunction("GetBool",&Component::GetBoolValue)
                .addFunction("SetBool",&Component::SetBoolValue)
                .addFunction("GetSubcomponent", &Component::GetSubcomponent)

            .endClass()
            .beginClass<Subscription>("Subscription")
                .addConstructor<void (*)(int)>()
            .endClass()
            .beginClass<EventType>("EventType")
                .addStaticData("HEALTH_UPDATE_EVENT", &EventType::HEALTH_UPDATE_EVENT, false)
                .addStaticData("COLLISION_EVENT", &EventType::COLLISION_EVENT, false)
                .addStaticData("DAMAGE_EVENT", &EventType::DAMAGE_EVENT, false)
                .addStaticData("DELETE_ENTITY_EVETN", &EventType::DELETE_ENTITY_EVENT, false)
                .addStaticData("CONDITION_ADD_EVENT", &EventType::CONDITION_ADD_EVENT, false)
                .addStaticData("W_DOWN_EVENT", &EventType::W_DOWN_EVENT, false)
                .addStaticData("W_UP_EVENT", &EventType::W_UP_EVENT, false)
                .addStaticData("S_DOWN_EVENT", &EventType::S_DOWN_EVENT, false)
                .addStaticData("S_UP_EVENT", &EventType::S_UP_EVENT, false)
            .endClass()
            .beginClass<Event>("Event")
                .addConstructor<void (*) (int,int,int, void*)>()
                .addData("id", &Event::id)
                .addData("sender", &Event::sender_id)
                .addData("target", &Event::target_id)
                .addFunction("ExtraInfoAsInit", &Event::ExtraInfoAsInt)
            .endClass()
            .beginClass<EventManager>("EventManager")
                .addStaticFunction("Instance", &EventManager::Instance)
                .addFunction("LaunchEvent",&EventManager::LaunchEvent)
            .endClass()
            .beginClass<ComponentUserBase>("ComponentUsers")
                .addStaticFunction("Instance",&ComponentUserBase::Instance)
                .addFunction("GetAll",&ComponentUserBase::GetAllUsersWithComponentsAsLuaList)
                .addFunction("GetAllEntities",&ComponentUserBase::GetAllEntitesWithComponentAsLuaList)
            .endClass()
            .beginClass<LuaRef>("LuaRef")
            .endClass()
            .beginClass<GameWindow>("GameWindow")
                .addStaticFunction("Instance", &GameWindow::Instance)
                .addFunction("Draw",&GameWindow::DrawFromComponents)
            .endClass()
            .beginClass<KeyboardController>("Keyboard")
                .addStaticFunction("Instance", &KeyboardController::Instance)
                .addFunction("Get",&KeyboardController::Get)
            .endClass()
            .beginClass<Instance>("Instance")
            .endClass()
            .deriveClass<LuaInstance,Instance>("LuaInstance")
            .endClass()
            .beginClass<Stage>("Stage")
            .endClass()
            .deriveClass<LuaStage, Stage>("LuaStage")
            .endClass()
            .beginClass<Tile>("Tile")
            .endClass()
            .beginClass<DebugFlags>("DebugFlags")
                .addStaticFunction("Instance", &DebugFlags::Instance)
                .addFunction("Set", &DebugFlags::Set)
            .endClass();
        } 
 };

 #endif