#include "GameRunner.h"

GameRunner::GameRunner()
{
    _last_time = std::chrono::time_point<std::chrono::high_resolution_clock>::min();
    _game_window = GameWindow::Instance();
}

void GameRunner::Start()
{
    _game_window->Init();
}

void GameRunner::Update()
{
    if(_last_time == std::chrono::time_point<std::chrono::high_resolution_clock>::min())
        _last_time = std::chrono::high_resolution_clock::now();
        
    auto current_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - _last_time); 

    double seconds_elapsed_since_last_update = std::abs(diff.count());

    if(seconds_elapsed_since_last_update  > (1.0 /  (FRAMES_PER_SEC)))
    {
        UpdateSystems(seconds_elapsed_since_last_update);
        UpdateGui(seconds_elapsed_since_last_update);
        _last_time = current_time;
    }
}

int GameRunner::UpdateSystems(float time)
{
    SystemController::Instance()->Update(time);
    return 0;

}

int GameRunner::UpdateGui(float time)
{
    _game_window->Update(time);
    return 0;
}