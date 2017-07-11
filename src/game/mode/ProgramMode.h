#ifndef PROGRAMMODE_H
#define PROGRAMMODE_H

#include "src/game/gui/PMIDGWindow.h"

class ProgramMode
{  
 public:
    virtual void Update(float seconds_elapsed) = 0;
    virtual void Render(PMIDGWindow& window, float seconds_elapsed) = 0;
    virtual void Init(PMIDGWindow& window) = 0;
    virtual void Exit() = 0;
};
#endif