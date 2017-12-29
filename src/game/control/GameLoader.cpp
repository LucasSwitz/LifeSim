#include "src/game/control/GameLoader.h"

void GameLoader::Load(std::string file_path, std::string file_name, GameState &state)
{
    Load(file_path + "/" + file_name, state);
}

void GameLoader::Load(std::string file_path, GameState &state)
{
    std::cout << "Loading game from file: " << file_path << std::endl;
    GameStateProtoBufWrapper gameStateProtoBuf;
    gameStateProtoBuf.FromFile(file_path);
    GameStateFromProtoBuf(gameStateProtoBuf, state);
}

void GameLoader::Save(const std::string &file_path, const std::string &file_name, GameState &state)
{
    Save(file_path + "/" + file_name, state);
}

void GameLoader::Save(std::string file_name, GameState &game_state)
{
    std::cout << "Saving game to file: " << file_name << std::endl;
    GameStateProtoBufWrapper gameStateProtoBuf;
    gameStateProtoBuf.SetStage(*game_state.GetStage());
    gameStateProtoBuf.SetEntities(game_state.GetEntityManager().GetAllEntities());
    gameStateProtoBuf.SetSystems(game_state.GetSystemController().GetExecutionSequence());
    gameStateProtoBuf.ToFile(file_name);
}

void GameLoader::GameStateFromProtoBuf(GameStateProtoBufWrapper &protobuf, GameState &game_state)
{
    /*std::list<Entity *> entities;
    std::list<std::string> systems;
    ptr<LuaStage> stage = std::make_shared<LuaStage>();

    protobuf.GetEntities(entities);
    protobuf.GetSystems(systems);

    protobuf.GetStage(stage);
    game_state.SetStage(stage);

    for (Entity *e : entities)
    {
        game_state.AddEntity(ptr<Entity>(e));
    }

    for (std::string &system : systems)
    {
        game_state.AddSystem(system);
    }*/
}