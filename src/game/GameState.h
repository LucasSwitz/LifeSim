#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "src/component/ComponentUserBase.h"
#include "src/game_objects/EntityManager.h"
#include "src/event/EventManager.h"
#include "src/system/SystemController.h"
#include "src/game/player/PlayerBase.h"

#include "src/game/FPSRunnable.h"
#include "src/world/stage/Stage.h"
/**
    Purpose: GameState describes all game operating specific details. This includes 
             information about active entities, running systems, loaded instances, etc.
             A GameState can be operated by an FPSRunnable.
**/

class GameState : public FPSRunnable, public std::enable_shared_from_this<GameState> 
{
public:
  GameState();

  GameState(const GameState &game_state);

  void Load();

  void Setup();

  void Tick(float seconds_elapsed);

  void Unload();

  void SetStage(ptr<Stage> stage);

  void ChangeState(ptr<Stage> new_stage);

  void AddSystem(std::string system_name);

  void AddSystem(ptr<System> system);

  void AddEntity(ptr<Entity> e);

  ptr<Stage> GetStage();

  ComponentUserBase* GetComponentUserBase();

  ptr<EntityManager> GetEntityManager();

  SystemController &GetSystemController();

  EventManager &GetMessageDispatch();

  PlayerBase &GetPlayerBase();

private:
  SystemController _system_controller;
  EventManager _message_dispatch;
  PlayerBase _player_base;
  ptr<Stage> _current_stage = nullptr;
};
#endif