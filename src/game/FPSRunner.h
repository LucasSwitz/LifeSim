#ifndef FPSRUNNER_H
#define FPSRUNNER_H


#include "src/game/FPSRunnable.h"

class FPSRunner
{
  public:

    FPSRunner()
    {

    }

    void Update(float seconds_elapsed)
    {    
        RunGameSystems(seconds_elapsed);

        if(_runnable)
            _runnable->Update(seconds_elapsed);    
    }

    void RunGameSystems(float seconds_elapsed)
    {
        SystemController::Instance()->Update(seconds_elapsed); //change this game specific systems
    }

    void SetRunnable(FPSRunnable* runnable)
    {
        _runnable = runnable;
    }

    void OnSFEvent(sf::Event& event)
    {

    }

    protected:
        FPSRunnable* _runnable = nullptr;
};

#endif