#ifndef PROGRAMMODE_H
#define PROGRAMMODE_H

#include "src/graphics/gui/PMIDGWindow.h"

class ProgramMode
{  
 public:
    ProgramMode(PMIDGWindow* window) : _window(window){}
    virtual void Update(float current_time) = 0;
    virtual void Render(float current_time) = 0;
    virtual void Exit() = 0;
 protected:
    PMIDGWindow* _window;
};
#endif