#include "src/game/TBGameRunner.h"

TBGameRunner::TBGameRunner() : FPSRunner(GAME_FPS)
{

}

void TBGameRunner::RunGameState(const std::string &file_path)
{
}

void TBGameRunner::RunGameState(GameState &game_state)
{
   _game_state = ptr<GameState> (new GameState(game_state));
    Run();
}

void TBGameRunner::RunGameState(GameState &game_state, int instance_id)
{
    _game_state = ptr<GameState> (new GameState(game_state));
    _game_state->GetStage()->SetCurrentInstance(instance_id);
    Run();
}

void TBGameRunner::Run()
{
    SetRunnable(_game_state.get());
    _game_state->Setup();
}

void TBGameRunner::CreateGameState()
{

    _game_state = ptr<GameState> (new GameState());
    SetRunnable(_game_state.get());
}

void TBGameRunner::Tick(float seconds_elapsed)
{

}

void TBGameRunner::Load()
{
}

void TBGameRunner::Unload()
{
}

void TBGameRunner::SetListener(TBGameRunnerListener* listener)
{
    _listener = listener;
}

void TBGameRunner::OnEvent(Event &e)
{
    if (e.id == EventType::CLOSE_WINDOW_EVENT)
    {
        Shutdown();
    }
}

void TBGameRunner::Shutdown()
{
    if (_listener)
        _listener->OnGameRunnerShutdown();
}

std::list<Subscription> TBGameRunner::GetSubscriptions()
{
    //std::list<Subscription> subs = {Subscription(EventType::CLOSE_WINDOW_EVENT, {_window.ID()})};

    return {};
}

ptr<GameState> TBGameRunner::GetGameState()
{
    return _game_state;
}

TBGameRunner::~TBGameRunner()
{
    
}