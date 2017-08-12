#ifndef GAMELOADER_H
#define GAMELOADER_H

#include "src/game/GameState.h"
#include "src/protobuf/wrappers/GameStateProtoBufWrapper.h"

/**
    Purpose: A GameLoader instance can be used to load implementation specific
             details into a GameState instance. This class depends on GameStateProtoBufWrapper to
             import/export GameState data to/from serialized forms.
**/

class GameLoader
{
  public:
    void Load(std::string file_path, std::string file_name, GameState &state)
    {
        Load(file_path + "/" + file_name, state);
    }

    void Load(std::string file_path, GameState &state)
    {
        std::cout << "Loading game from file: " << file_path << std::endl;
        GameStateProtoBufWrapper gameStateProtoBuf;
        gameStateProtoBuf.FromFile(file_path);
        GameStateFromProtoBuf(gameStateProtoBuf, state);
    }

    void Save(const std::string &file_path, const std::string &file_name, GameState &state)
    {
        Save(file_path + "/" + file_name, state);
    }

    void Save(std::string file_name, GameState &game_state)
    {
        std::cout << "Saving game to file: " << file_name << std::endl;
        GameStateProtoBufWrapper gameStateProtoBuf;
        gameStateProtoBuf.SetInstance(*game_state.GetInstance());
        gameStateProtoBuf.SetEntities(game_state.GetEntityManager().GetAllEntities());
        gameStateProtoBuf.SetSystems(game_state.GetSystemController().GetExecutionSequence());
        gameStateProtoBuf.ToFile(file_name);
    }

    void GameStateFromProtoBuf(GameStateProtoBufWrapper &protobuf, GameState &game_state)
    {
        std::list<Entity *> entities;
        std::list<std::string> systems;
        Instance *instance = new Instance();

        protobuf.GetEntities(entities);
        protobuf.GetSystems(systems);
        protobuf.GetInstance(instance);

        for (Entity *e : entities)
        {
            game_state.AddEntity(e);
        }

        for (std::string &system : systems)
        {
            game_state.AddSystem(system);
        }

        instance->GetTileMap().Show();
        game_state.SetCurrentInstance(instance);
    }
};
#endif