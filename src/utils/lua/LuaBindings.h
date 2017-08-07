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
#include "src/game_objects/LuaEntityFactory.h"
#include "src/component/ComponentUserBase.h"
#include "src/component/ComponentUser.h"
#include "src/controllers/Keyboard.h"
#include "src/world/tile/Tile.h"
#include "src/world/stage/Stage.h"
#include "src/world/stage/Instance.h"
#include "src/utils/debug/DebugFlags.h"
#include "src/world/stage/LuaInstance.h"
#include "src/world/stage/LuaStage.h"
#include "src/graphics/gui/PMIDGWindow.h"
#include "src/event/messaging/MessageDispatch.h"
#include "src/event/EngineEventManager.h"
#include "src/controllers/PlayerController.h"
#include "src/controllers/ControllerBase.h"
#include "src/game/resources/ResourceManager.h"

using namespace luabridge;
class LuaBindings
    {
    public:
        static void Bind(lua_State *L)
        { 
            getGlobalNamespace(L)
            .addFunction("Res",&ResourceManager::GetResource)
            .beginClass<ComponentUser>("ComponentUser")
                .addFunction("GetNumber", &ComponentUser::GetComponentValueFloat)
                .addFunction("SetNumber", &ComponentUser::SetComponentValueFloat)
                .addFunction("GetString", &ComponentUser::GetComponentValueString)
                .addFunction("SetString", &ComponentUser::SetComponentValueString)
                .addFunction("SetBool", &ComponentUser::SetComponentBoolValue)
                .addFunction("GetBool", &ComponentUser::GetComponentBoolValue)
                .addFunction("GetComponent", &ComponentUser::GetComponent)
                .addFunction("HasComponent",&ComponentUser::HasComponent)
                .addProperty("id",&ComponentUser::ID)
            .endClass()
            .deriveClass<Entity, ComponentUser>("Entity")
                .addConstructor<void(*)(void)>()
                .addFunction("IsType", &Entity::IsType)
                .addFunction("Call", &Entity::CallFunction)
                .addStaticData("CPP_DEFINED_ENTITY", &Entity::CPP_DEFINED_ENTITY)
                .addStaticData("LUA_DEFINED_ENTITY", &Entity::LUA_DEFINED_ENTITY)
                .addStaticFunction("Downcast",&Entity::DowncastFromComponentUser)
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
                .addConstructor<void (*)(void)>()
                .addFunction("Iterator", &LuaList<ComponentUser*>::Iterator)
                .addFunction("Size",&LuaList<ComponentUser*>::Size)
            .endClass()
            .beginClass<LuaList<Entity*>>("LuaListEntity")
                .addConstructor<void (*)(void)>()
                .addFunction("Iterator", &LuaList<Entity*>::Iterator)
                .addFunction("Size",&LuaList<Entity*>::Size)
            .endClass()
            .beginClass<EntityManager>("EntityManager")
                .addStaticFunction("Instance", &EntityManager::Instance)
                .addFunction("size", &EntityManager::GetNumberOfEntities)
                .addFunction("Get", &EntityManager::GetEntityByID)
                .addFunction("AsLuaList", &EntityManager::AsLuaList)
                .addFunction("Last",&EntityManager::GetNewest)
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
                .addStaticData("DELETE_ENTITY_EVENT", &EventType::DELETE_ENTITY_EVENT, false)
                .addStaticData("CONDITION_ADD_EVENT", &EventType::CONDITION_ADD_EVENT, false)
                .addStaticData("W_DOWN_EVENT", &EventType::W_DOWN_EVENT, false)
                .addStaticData("W_UP_EVENT", &EventType::W_UP_EVENT, false)
                .addStaticData("S_DOWN_EVENT", &EventType::S_DOWN_EVENT, false)
                .addStaticData("S_UP_EVENT", &EventType::S_UP_EVENT, false)
                .addStaticData("DRAW_REQUEST_EVENT",&EventType::DRAW_REQUEST_EVENT,false)
                .addStaticData("SPAWN_ENTITY_EVENT",&EventType::SPAWN_ENTITY_EVENT,false)
            .endClass()
            .beginClass<Event>("Event")
                .addConstructor<void (*)(int,int,int)>()
                .addStaticFunction("ComponentUserEvent",&Event::Create<ComponentUser>)
                .addStaticFunction("EntityEvent",&Event::Create<Entity>)
                .addData("id", &Event::id)
                .addData("sender", &Event::sender_id)
                .addData("target", &Event::target_id)
            .endClass()
            .beginClass<EventManager>("EventManager")
                .addFunction("LaunchEvent",&EventManager::LaunchEvent)
            .endClass()
            .deriveClass<MessageDispatch,EventManager>("MessageDispatch")
                .addStaticFunction("Instance",&MessageDispatch::Instance)
            .endClass()
            .deriveClass<EngineEventManager,EventManager>("EngineEventManager")
                .addStaticFunction("Instance",&EngineEventManager::Instance)
            .endClass()
            .beginClass<ComponentUserBase>("ComponentUsers")
                .addStaticFunction("Instance",&ComponentUserBase::Instance)
                .addFunction("GetAll",&ComponentUserBase::GetAllUsersWithComponentsAsLuaList)
                .addFunction("GetAllEntities",&ComponentUserBase::GetAllEntitesWithComponentAsLuaList)
            .endClass()
            .beginClass<LuaRef>("LuaRef")
            .endClass()
            .beginClass<IODevice>("IODevice")
                .addFunction("Get",&IODevice::Get)
            .endClass()
            .deriveClass<KeyboardController, IODevice>("Keyboard")
                .addStaticFunction("Instance", &KeyboardController::Instance)
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