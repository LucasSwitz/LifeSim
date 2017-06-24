#ifndef GAMERUNNER_H
#define GAMERUNNER_H

#include <chrono>
#include "src/system/SystemController.h"

#define FRAMES_PER_SEC 30


class GameRunner
{
  public:
    GameRunner();
    void Update();

  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _last_time;
};

#endif