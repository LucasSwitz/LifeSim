#ifndef PROGRAMMODE_H
#define PROGRAMMODE_H

#include "src/game/gui/PMIDGWindow.h"

class ProgramMode
{  
 public:
    ProgramMode(PMIDGWindow* window) : _window(window){}
    virtual void Update(float seconds_elapsed) = 0;
    virtual void Render(float seconds_elapsed) = 0;
    virtual void Exit() = 0;
 protected:
    PMIDGWindow* _window;
};
#endif