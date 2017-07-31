#ifndef PMIDGMODEGAME_H
#define PMIDGMODEGAME_H

#include "src/graphics/gui/PMIDGWindow.h"
#include "src/utils/SingletonRotary.h"

#define GAME_FPS 30

class PMIDGModeGame : public GameMode
{
    public:
    PMIDGModeGame(PMIDGWindow* window) : ProgramMode(window){}

    void Enter()
    {
        
    }

    void Update(float seconds_elapsed)
    {
        _game_state->Tick(seconds_elapsed);
    }

    void Render(float seconds_elapsed)
    {
        
    }

    void Exit()
    {

    }

    private:
        GameRunner* _game_runner;
};

#endif