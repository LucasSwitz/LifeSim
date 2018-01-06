#ifndef GAMELOADER_H
#define GAMELOADER_H

#include "src/game/GameState.h"
#include "src/world/stage/LuaStage.h"
#include "src/protobuf/wrappers/GameStateProtoBufWrapper.h"

/**
    Purpose: A GameLoader instance can be used to load implementation specific
             details into a GameState instance. This class depends on GameStateProtoBufWrapper to
             import/export GameState data to/from serialized forms.
**/

class GameLoader
{
  public:
    void Load(std::string file_path, std::string file_name, GameState &state, ComponentUserBase& cub);

    void Load(std::string file_path, GameState &state, ComponentUserBase& cub);

    void Save(const std::string &file_path, const std::string &file_name, GameState &state);

    void Save(std::string file_name, GameState &game_state);

    void GameStateFromProtoBuf(GameStateProtoBufWrapper &protobuf, GameState &game_state, ComponentUserBase& cub);
};
#endif