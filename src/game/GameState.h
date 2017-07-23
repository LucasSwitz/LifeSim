#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "src/component/ComponentUserBase.h"
#include "src/game_objects/EntityManager.h"
#include "src/event/messaging/MessageDispatch.h"
#include "src/system/SystemController.h"

#include "src/game/FPSRunnable.h"
#include "src/world/stage/Instance.h"

class GameState : public FPSRunnable
{
  public:
    void Load()
    {
        Setup();
    }

    void Setup()
    {
        EntityManager::GiveOwnership(&_entity_manager);
        ComponentUserBase::GiveOwnership(&_component_users);
        SystemController::GiveOwnership(&_system_controller);
        MessageDispatch::GiveOwnership(&_message_dispatch);
    }

    void Tick(float seconds_elapsed)
    {
        _system_controller.Update(seconds_elapsed);

        if (_current_instance)
            _current_instance->Tick(seconds_elapsed);
    }

    void Unload()
    {

    }

    void SetCurrentInstance(Instance *instance)
    {
        _current_instance = instance;
    }

    void AddSystem(std::string system_name)
    {
        _system_controller.AddToSystemExecutionSequence(system_name);
    }

    void AddSystem(System *system)
    {
        _system_controller.AddToSystemExecutionSequence(system);
    }

    void AddEntity(Entity* e)
    {
        _entity_manager.RegisterEntity(e);
        AddComponentUser(e);
    }

    void AddComponentUser(ComponentUser* user)
    {
        user->EnableAll();
    }

    GameState Copy()
    {

    }

    EntityManager& GetEntityManager()
    {
        return _entity_manager;
    }

    ComponentUserBase& GetComponentUserBase()
    {
        return _component_users;
    }

    SystemController& GetSystemController()
    {
        return _system_controller;
    }

    Instance* GetInstance()
    {
        return _current_instance;
    }

  private:
    EntityManager _entity_manager;
    ComponentUserBase _component_users;
    SystemController _system_controller;
    MessageDispatch _message_dispatch;
    Instance *_current_instance;
};
#endif