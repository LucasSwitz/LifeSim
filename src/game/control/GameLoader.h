#ifndef GAMELOADER_H
#define GAMELOADER_H

#include "src/game/GameState.h"
#include "src/protobuf/wrappers/GameStateProtoBufWrapper.h"

class GameLoader
{
    public:
        void Load(std::string file_name, GameState& state)
        {
            GameStateProtoBufWrapper gameStateProtoBuf;
            gameStateProtoBuf.FromFile(file_name);
            GameStateFromProtobuf(GameStateFromProtoBuf, state);
        }

        void Save(std::string file_name, GameState& game_state)
        {
            GameStateProtoBufWrapper gameStateProtoBuf;
            gameStateProtoBuf.SetInstance(game_state.GetCurrentInstance());
            gameStateProtoBuf.SetEntities(game_entity.EntityMananger()->GetAllEntities());
            gameStateProtoBuf.SetSystems(game_state.SystemController()->GetAllSystems());
            gameStateProtoBuf.ToFile(file_name);
        }

        void GameStateFromProtoBuf(GameStateProtoBufWrapper& protobuf, GameState* game_state)
        {
            // Get all entities from protobuf and add them
            // Get all systems from protobuf and add them
            // Get Instance and set it
        
        }   
};
#endif