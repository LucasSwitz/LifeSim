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

    void RunStage(Stage stage)
    {
    }

    void RunInstance(Instance &instance)
    {
        if (!_game_state)
            CreateGameState();

        Instance *copy_instance = new Instance(instance);
        _game_state->SetCurrentInstance(copy_instance);
        _game_state->Setup();
    }

    void RunGameState(const std::string &file_path)
    {
    }

    virtual void Update(std::chrono::time_point<std::chrono::high_resolution_clock> &current_time)
    {
        FPSRunner::Update(current_time);
    }

    void RunGameState(GameState &game_state)
    {
        if (_game_state)
            delete _game_state;

        _game_state = new GameState(game_state);
        SetRunnable(_game_state);
        _game_state->Setup();
        _window.Focus();
        _game_state->GetInstance()->Open();
        SystemController::Instance()->AddToSystemExecutionSequence("FollowCharacterCamera");    
    }

    void CreateGameState()
    {
        if (_game_state)
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
        std::cout << "Unloaded!" << std::endl;
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