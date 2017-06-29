#ifndef GAMERUNNER_H
#define GAMERUNNER_H

#include <chrono>
#include "src/system/SystemController.h"
#include "src/gui/GameWindow.h"

#define FRAMES_PER_SEC 30

/**
  GameRunner runs the game at a specified FPS.
**/
class GameRunner
{
  public:
    GameRunner();
    void Update();
    void Start();

  private:

    int UpdateSystems(float time);
    int UpdateGui(float time);
    std::chrono::time_point<std::chrono::high_resolution_clock> _last_time;
    GameWindow _game_window;
};

#endif