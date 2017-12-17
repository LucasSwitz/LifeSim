#ifndef PMIDGGAMERUNNER
#define PMIDGGAMERUNNER

#include "src/game/GameState.h"
#include "src/game/FPSRunner.h"
#include "src/graphics/gui/PMIDGWindow.h"

#define GAME_FPS 30

class PMIDGGameRunnerListener
{
  public:
    virtual void OnGameRunnerShutdown() = 0;
};

class PMIDGGameRunner : public FPSRunner, public FPSRunnable, public EventSubscriber
{

  public:
    PMIDGGameRunner();
    ~PMIDGGameRunner();

    void RunGameState(const std::string &file_path);

    void RunGameState(GameState &game_state);

    void RunGameState(GameState &game_state, int instance_id);

    void Run();

    void CreateGameState();

    void Tick(float seconds_elapsed) override;

    void Load();

    void Unload();

    void SetListener(PMIDGGameRunnerListener* listener);

    void OnEvent(Event &e);

    void Shutdown();

    std::list<Subscription> GetSubscriptions();

  private:
    PMIDGWindow _window;
    ptr<GameState> _game_state = nullptr;
    PMIDGGameRunnerListener* _listener = nullptr;
    bool _shutdown = false;
};
#endif