#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "src/component/ComponentUserBase.h"
#include "src/game_objects/EntityManager.h"
#include "src/event/messaging/MessageDispatch.h"
#include "src/system/SystemController.h"

#include "src/game/FPSRunnable.h"
#include "src/world/stage/Stage.h"

/**
    Purpose: GameState describes all game operating specific details. This includes 
             information about active entities, running systems, loaded instances, etc.
             A GameState can be operated by an FPSRunnable.
**/

class GameState : public FPSRunnable
{
  public:
    GameState()
    {
        _message_dispatch.RegisterSubscriber(&_system_controller);
    };

    GameState(const GameState &game_state) : _message_dispatch(),
                                             _entity_manager(game_state._entity_manager, _component_users),
                                             _system_controller(game_state._system_controller),
                                             _current_stage(game_state._current_stage)
    {
        _message_dispatch.RegisterSubscriber(&_system_controller);
        //all the things need to add themselves to the component user base
    }

    void Load()
    {
    }

    void Setup()
    {
        MessageDispatch::GiveOwnership(&_message_dispatch);
        ComponentUserBase::GiveOwnership(&_component_users);
        EntityManager::GiveOwnership(&_entity_manager);
        SystemController::GiveOwnership(&_system_controller);
    }

    void Tick(float seconds_elapsed)
    {

        if (_current_stage && _current_stage->GetCurrentInstance())
        {
            _system_controller.Update(seconds_elapsed);
            _current_stage->Tick(seconds_elapsed);
        }

        _entity_manager.Clean();

        //if using lua
        LuaUniversal::Instance()->CollectGarbage();
    }

    void Unload()
    {
    }

    void SetStage(Stage *stage)
    {
        _current_stage = stage;
        _current_stage->Load();
        _current_stage->Enter();
    }

    void ChangeState(Stage *new_stage)
    {
        if (_current_stage)
        {
            _current_stage->Exit();
            _current_stage->Unload();
        }

        SetStage(new_stage);
    }

    void AddSystem(std::string system_name)
    {
        _system_controller.AddToSystemExecutionSequence(system_name);
    }

    void AddSystem(System *system)
    {
        _system_controller.AddToSystemExecutionSequence(system);
    }

    void AddEntity(Entity *e)
    {
        _entity_manager.RegisterEntity(e);
    }

    Stage *GetStage()
    {
        return _current_stage;
    }

    EntityManager &GetEntityManager()
    {
        return _entity_manager;
    }

    ComponentUserBase &GetComponentUserBase()
    {
        return _component_users;
    }

    SystemController &GetSystemController()
    {
        return _system_controller;
    }

  private:
    ComponentUserBase _component_users;
    SystemController _system_controller;
    MessageDispatch _message_dispatch;
    EntityManager _entity_manager;
    Stage *_current_stage = nullptr;
};
#endif