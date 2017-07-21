#ifndef FPSRUNNER_H
#define FPSRUNNER_H

#include <chrono>
#include <cmath>
#include "src/game/FPSRunnable.h"
#include "src/system/SystemController.h"

class FPSRunner
{
  public:
    FPSRunner(int FPS) : _fps(FPS)
    {

    }

    void Update(std::chrono::time_point<std::chrono::high_resolution_clock>& current_time)
    {
        if (_last_time == std::chrono::time_point<std::chrono::high_resolution_clock>::min())
            _last_time = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> diff = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - _last_time);

        double seconds_elapsed_since_last_update = std::abs(diff.count());

        if (seconds_elapsed_since_last_update > (1.0 / (_fps)))
        {
            Tick(seconds_elapsed_since_last_update);
            TickRunnable();
            _last_time = current_time;
        }
    }

    virtual void Tick(float seconds_elapsed) = 0;

    void TickRunnable(float seconds_elapsed)
    {
        if (_runnable)
            _runnable->Tick(seconds_elapsed);
    }

    void SetRunnable(FPSRunnable *runnable)
    {
        _runnable = runnable;
    }

  protected:
    FPSRunnable *_runnable = nullptr;
    std::chrono::time_point<std::chrono::high_resolution_clock> _last_time;
    int _fps;
};

#endif