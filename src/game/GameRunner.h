#ifndef GAMERUNNER_H
#define GAMERUNNER_H

#include "src/game/FPSRunner.h"
#include "src/game/GameState.h"

class GameRunner : public FPSRunner
{
    public:
        GameRunner(int fps) : FPSRunner(fps)
        {

        }

        void SetGameState(GameState* game_state)
        {
            _game_state = game_state;
            this->SetRunnable(_game_state);
        }

    private:
        GameState* _game_state;        
};
#endif