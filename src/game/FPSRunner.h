#ifndef FPSRUNNER_H
#define FPSRUNNER_H

#include <chrono>
#include <cmath>
#include "src/game/FPSRunnable.h"
#include "src/system/SystemController.h"

/**
        Purpose: An FPS Runner can be used to tick and FPSRunner at a given frequency.
        Tick frequency is determined by the provided FPS parameter. 
**/

class FPSRunner
{
  public:
    FPSRunner(int FPS);

    virtual void Update(std::chrono::time_point<std::chrono::high_resolution_clock>& current_time);

    void TickRunnable(float seconds_elapsed);

    void SetRunnable(ptr<FPSRunnable> runnable);

    void CleanRunnable();

  protected:
    ptr<FPSRunnable> _runnable = nullptr;
    std::chrono::time_point<std::chrono::high_resolution_clock> _last_time  
      = std::chrono::time_point<std::chrono::high_resolution_clock>::min();
    int _fps;
};

#endif