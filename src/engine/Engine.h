#ifndef ENGINE_H
#define ENGINE_H

#include "src/utils/json/json.hpp"
#include "src/system/SystemController.h"
#include "src/game/FPSRunner.h"
#include "src/game/TBGameRunner.h"
#include <fstream>

class Engine : public FPSRunnable, public FPSRunner
{

  public:
    Engine(const std::string config_file = "") : FPSRunner(60)
    {
        _engine_event_manager.RegisterSubscriber(&_system_controller);
        if (!config_file.empty())
        {
            Load(config_file);
        }

        SetRunnable(&_game_runner);
    }

    void Load(const std::string &file)
    {
        std::ifstream input(file);

        json engine_json;
        input >> engine_json;

        Load(engine_json);
    }

    using json = nlohmann::json;
    void Load(const json &engine_json)
    {
        auto systems = engine_json["systems"];

        for (auto it = systems.begin(); it != systems.end(); it++)
        {
            std::string system = *it;
            _system_controller.AddToSystemExecutionSequence(system);
        }
    }

    void Load(){}

    void Update(std::chrono::time_point<std::chrono::high_resolution_clock> &current_time)
    {
        _game_runner.Update(current_time);
    }

    void Tick(float seconds_elapsed)
    {
        _system_controller.Update(seconds_elapsed, this);
    }

    void Unload()
    {
    }

    void AddSystem(const std::string &system_name)
    {
        _system_controller.AddToSystemExecutionSequence(system_name);
    }

    ptr<GameState> GetGameState()
    {
        return _game_runner.GetGameState();
    }

    EventManager &GetEngineEventManager()
    {
        return _engine_event_manager;
    }

    ComponentUserBase &GetComponentUserBase()
    {
        return _cub;
    }

    void LoadGameState(ptr<GameState> gs)
    {
        _game_runner.SetRunnable(gs.get());
    }

    bool SystemIsRunning(const std::string& system_name)
    {
        return _system_controller.HasSystem(system_name);
    }

  private:
    SystemController<Engine> _system_controller;
    EventManager _engine_event_manager;
    TBGameRunner _game_runner;
    ComponentUserBase _cub;
};

#endif