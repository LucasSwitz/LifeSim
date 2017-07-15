#ifndef GAMERUNNER_H
#define GAMERUNNER_H

#include "src/system/SystemController.h"
#include "src/world/stage/Stage.h"
#include "src/world/stage/LuaStageFactory.h"
#include "src/world/tile/LuaTileFactory.h"


#define FRAMES_PER_SEC 30

/**
  GameRunner runs the game at a specified FPS.
**/
class GameRunner
{
  public:
    GameRunner();
    void Update(float seconds_elapsed);
    void Init();
    void Shutdown();
    void OnEvent(Event& e);
    void ChangeStage(Stage* stage);
    int UpdateStage(float seconds);
    bool Initialized();
    Stage* GetCurrentStage();
    std::list<Subscription> GetSubscriptions();

  private:

    int UpdateSystems(float time);
    Stage* _current_stage = nullptr;
    bool _initialized;
};

#endif