#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "src/component/ComponentUserBase.h"
#include "src/game_objects/EntityManager.h"
#include "src/event/messaging/MessageDispatch.h"
#include "src/system/SystemController.h"
#include "src/game/player/PlayerBase.h"

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
    GameState();

    GameState(const GameState &game_state);

    void Load();

    void Setup();

    void Tick(float seconds_elapsed);

    void Unload();

    void SetStage(Stage *stage);

    void ChangeState(Stage *new_stage);

    void AddSystem(std::string system_name);

    void AddSystem(System *system);

    void AddEntity(Entity *e);

    Stage *GetStage();

    EntityManager &GetEntityManager();

    ComponentUserBase &GetComponentUserBase();

    SystemController &GetSystemController();

  private:
    ComponentUserBase _component_users;
    SystemController _system_controller;
    MessageDispatch _message_dispatch;
    EntityManager _entity_manager;
    PlayerBase _player_base;
    Stage *_current_stage = nullptr;
};
#endif