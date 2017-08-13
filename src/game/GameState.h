#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "src/component/ComponentUserBase.h"
#include "src/game_objects/EntityManager.h"
#include "src/event/messaging/MessageDispatch.h"
#include "src/system/SystemController.h"

#include "src/game/FPSRunnable.h"
#include "src/world/stage/Instance.h"

/**
    Purpose: GameState describes all game operating specific details. This includes 
             information about active entities, running systems, loaded instances, etc.
             A GameState can be operated by an FPSRunnable.
**/

class GameState : public FPSRunnable
{
  public:

    GameState(){};
    GameState(const GameState& game_state) : _message_dispatch(), 
                                             _entity_manager(game_state._entity_manager, _component_users),
                                             _system_controller(game_state._system_controller),
                                             _current_instance(game_state._current_instance)
    {
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
        _system_controller.Update(seconds_elapsed);

        if (_current_instance)
            _current_instance->Tick(seconds_elapsed);

        _entity_manager.Clean();
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

    void AddEntity(Entity *e)
    {
        _entity_manager.RegisterEntity(e);
     }

    GameState Copy()
    {
        
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

    Instance *GetInstance()
    {
        return _current_instance;
    }

  private:
    ComponentUserBase _component_users;
    SystemController _system_controller;
    MessageDispatch _message_dispatch;
    EntityManager _entity_manager;

    Instance *_current_instance = nullptr;
};
#endif