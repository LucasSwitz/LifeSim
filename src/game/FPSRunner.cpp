#include "src/game/FPSRunner.h"

FPSRunner::FPSRunner(int FPS) : _fps(FPS) {}

void FPSRunner::Update(std::chrono::time_point<std::chrono::high_resolution_clock> &current_time)
{
    if (_last_time == std::chrono::time_point<std::chrono::high_resolution_clock>::min())
        _last_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - _last_time);

    double seconds_elapsed_since_last_update = std::abs(diff.count());
    if (seconds_elapsed_since_last_update > (1.0 / (_fps)))
    {
        TickRunnable(seconds_elapsed_since_last_update);
        _last_time = current_time;
    }
}

void FPSRunner::TickRunnable(float seconds_elapsed)
{
    if (_runnable)
        _runnable->Tick(seconds_elapsed);
}

void FPSRunner::SetRunnable(FPSRunnable *runnable)
{
    _runnable = runnable;
}

void FPSRunner::CleanRunnable()
{
    _runnable->Unload();
    delete _runnable;
}
