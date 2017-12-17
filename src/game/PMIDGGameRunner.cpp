#include "src/game/PMIDGGameRunner.h"

PMIDGGameRunner::PMIDGGameRunner() : FPSRunner(GAME_FPS)
{
    EngineEventManager::Instance()->RegisterSubscriber(this);
}

void PMIDGGameRunner::RunGameState(const std::string &file_path)
{
}

void PMIDGGameRunner::RunGameState(GameState &game_state)
{
   _game_state = ptr<GameState> (new GameState(game_state));
    Run();
}

void PMIDGGameRunner::RunGameState(GameState &game_state, int instance_id)
{
    _game_state = ptr<GameState> (new GameState(game_state));
    _game_state->GetStage()->SetCurrentInstance(instance_id);
    Run();
}

void PMIDGGameRunner::Run()
{
    SetRunnable(_game_state);
    _game_state->Setup();
    _window.Focus();
}

void PMIDGGameRunner::CreateGameState()
{

    _game_state = ptr<GameState> (new GameState());
    SetRunnable(_game_state);
}

void PMIDGGameRunner::Tick(float seconds_elapsed)
{
    _window.Clear();
    _window.PollEvents();
    _window.Render();
    _window.Display();
}

void PMIDGGameRunner::Load()
{
}

void PMIDGGameRunner::Unload()
{
}

void PMIDGGameRunner::SetListener(ptr<PMIDGGameRunnerListener> listener)
{
    _listener = listener;
}

void PMIDGGameRunner::OnEvent(Event &e)
{
    if (e.id == EventType::CLOSE_WINDOW_EVENT)
    {
        Shutdown();
    }
}

void PMIDGGameRunner::Shutdown()
{
    _window.Shutdown();

    if (_listener)
        _listener->OnGameRunnerShutdown();

    delete this;
}

std::list<Subscription> PMIDGGameRunner::GetSubscriptions()
{
    std::list<Subscription> subs = {Subscription(EventType::CLOSE_WINDOW_EVENT, {_window.ID()})};

    return subs;
}

PMIDGGameRunner::~PMIDGGameRunner()
{
    
}