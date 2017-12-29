#ifndef TBGAMERUNNER
#define TBGAMERUNNER

#include "src/game/GameState.h"
#include "src/game/FPSRunner.h"

#define GAME_FPS 30

class TBGameRunnerListener
{
  public:
    virtual void OnGameRunnerShutdown() = 0;
};

class TBGameRunner : public FPSRunner, public FPSRunnable, public EventSubscriber
{

  public:
    TBGameRunner();
    ~TBGameRunner();

    void RunGameState(const std::string &file_path);

    void RunGameState(GameState &game_state);

    void RunGameState(GameState &game_state, int instance_id);

    void Run();

    void CreateGameState();

    void Tick(float seconds_elapsed) override;

    void Load();

    void Unload();

    void SetListener(TBGameRunnerListener* listener);

    void OnEvent(Event &e);

    void Shutdown();

    std::list<Subscription> GetSubscriptions();

    ptr<GameState> GetGameState();

  private:
    ptr<GameState> _game_state = nullptr;
    TBGameRunnerListener* _listener = nullptr;
    bool _shutdown = false;
};
#endif