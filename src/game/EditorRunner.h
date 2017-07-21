#ifndef EDITORRUNNER_H
#define EDITORRUNNER_H

#include "src/game/FPSRunner.h"
#include "src/system/SystemController.h"

class EditorRunner : public FPSRunner
{
  public:
    EditorRunner(int FPS) : FPSRunner(FPS)
    {
        
    }

    virtual void Tick(float seconds_elapsed)
    {
        RunSystems(seconds_elapsed);
    }

    void RunSystems(float seconds_elapsed)
    {
        SystemController::Instance()->Update(seconds_elapsed); //change this game specific systems
    }
};

#endif