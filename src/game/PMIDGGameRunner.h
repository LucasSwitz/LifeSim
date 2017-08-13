#ifndef PMIDGGAMERUNNER
#define PMIDGGAMERUNNER
#include "src/game/GameState.h"

#define GAME_FPS 30

class PMIDGGameRunnerListener
{
  public:
    virtual void OnGameRunnerShutdown() = 0;
};

class PMIDGGameRunner : public FPSRunner, public FPSRunnable, public EventSubscriber
{

  public:
    PMIDGGameRunner() : FPSRunner(GAME_FPS)
    {
        EngineEventManager::Instance()->RegisterSubscriber(this);
    }

    void RunGameState(const std::string &file_path)
    {

    }

    void RunGameState(GameState &game_state)
    {
        if (_game_state)
            delete _game_state;

        _game_state = new GameState(game_state);
        Run();
    }

    void RunGameState(GameState &game_state, int instance_id)
    {
        if (_game_state)
            delete _game_state;

        _game_state = new GameState(game_state);
        _game_state->GetStage()->SetCurrentInstance(instance_id);
        Run();
    }

    void Run()
    {
        SetRunnable(_game_state);
        _game_state->Setup();
        _window.Focus();
    }

    void CreateGameState()
    {
        if (_game_state)
            delete _game_state;

        _game_state = new GameState();
        SetRunnable(_game_state);
    }

    void Tick(float seconds_elapsed) override
    {
        _window.Clear();
        _window.PollEvents();
        _window.Render();
        _window.Display();
    }

    void Load()
    {

    }
    
    void Unload()
    {
        
    }

    void SetListener(PMIDGGameRunnerListener *listener)
    {
        _listener = listener;
    }

    void OnEvent(Event &e)
    {
        if (e.id == EventType::CLOSE_WINDOW_EVENT)
        {
            Shutdown();
        }
    }

    void Shutdown()
    {
        _window.Shutdown();
        
        if (_listener)
            _listener->OnGameRunnerShutdown();

        delete this;
    }

    std::list<Subscription> GetSubscriptions()
    {
        std::list<Subscription> subs = {Subscription(EventType::CLOSE_WINDOW_EVENT, {_window.ID()})};

        return subs;
    }

    ~PMIDGGameRunner()
    {
        delete _game_state;
    }

  private:
    PMIDGWindow _window;
    GameState *_game_state = nullptr;
    PMIDGGameRunnerListener *_listener = nullptr;
    bool _shutdown = false;
};
#endif