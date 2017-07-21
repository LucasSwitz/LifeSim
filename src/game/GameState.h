#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "src/component/ComponentUserBase.h"
#include "src/game_objects/EntityManager.h"
#include "src/event/EventManager.h"
#include "src/system/SystemController.h"

#include "src/game/FPSRunnable.h"

class GameState : public FPSRunnable
{
    void Load() override
    {
        Setup();
    }

    void Setup()
    {
        EntityManager::Instance()->GiveOwnership(&_entity_manager);
        ComponentUserBase::Instance()->GiveOwnership(&_component_users);
        SystemController::Instane()->GiveOwnership(&_system_controller);
        EventManager::Instnace()->GiveOwnership(&_event_manager);
    }

    void Tick(float seconds_elapsed) override
    {
        
    }

    void Unload() override
    {

    }

    GameState Copy()
    {

    }

    static GameState* GetGameState()
    {

    }
    
    private:
        EntityManager _entity_manager;
        ComponentUserBase _component_users;
        SystemController _system_controller;
        EventManager _event_manager;
};
#endif