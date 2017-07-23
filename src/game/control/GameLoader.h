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
            GameStateFromProtoBuf(gameStateProtoBuf, state);
        }

            
        void Save(const std::string& file_path, const std::string& file_name, GameState& state)
        {
            Save(file_path + "//" + file_name, state);
        }

        void Save(std::string file_name, GameState& game_state)
        {
            GameStateProtoBufWrapper gameStateProtoBuf;
            gameStateProtoBuf.SetInstance(*game_state.GetInstance());
            gameStateProtoBuf.SetEntities(game_state.GetEntityManager().GetAllEntities());
            gameStateProtoBuf.SetSystems(game_state.GetSystemController().GetSystemInExecutionSequence());
            gameStateProtoBuf.ToFile(file_name);
        }

        void GameStateFromProtoBuf(GameStateProtoBufWrapper& protobuf, GameState& game_state)
        {
            std::list<Entity*> entities; 
            std::list<std::string> systems; 
            Instance* instance = new Instance();

        
            protobuf.GetEntities(entities);
            protobuf.GetSystems(systems);
            protobuf.GetInstance(instance);

            for(Entity* e : entities)
            {
                game_state.AddEntity(e);
            }

            for(std::string& system : systems)
            {
                game_state.AddSystem(system);
            }

            game_state.SetCurrentInstance(instance);
        }   
};
#endif