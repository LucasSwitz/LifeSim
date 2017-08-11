#ifndef PMIDGGAMERUNNER
#define PMIDGGAMERUNNER
#include "src/game/GameState.h"

#define GAME_FPS 30

class PMIDGGameRunner : public FPSRunner, public FPSRunnable
{

  public:

    PMIDGGameRunner() : FPSRunner(GAME_FPS)
    {

    }

    void RunStage(Stage stage)
    {
        
    }

    void RunInstance(Instance& instance)
    {
        if(!_game_state)
            CreateGameState();

        Instance* copy_instance = new Instance(instance);
        _game_state->SetCurrentInstance(copy_instance);
    }

    void RunGameState(const std::string& file_path)
    {

    }

    void RunGameState(GameState& game_state)
    {
        if(_game_state)
            delete _game_state;
        _game_state = new GameState(game_state);
        SetRunnable(_game_state);
    }

    void CreateGameState()
    {
        if(_game_state)
            delete _game_state;
        _game_state = new GameState();
        SetRunnable(_game_state);
    }

    void Load()
    {

    }

    void Tick(float seconds_elapsed)
    {
        _window.Clear();
        _window.PollEvents();
        _window.Render();
        _window.Display();
    }

    void Unload()
    {

    }

  private:
    PMIDGWindow _window;
    GameState* _game_state = nullptr;
};
#endif