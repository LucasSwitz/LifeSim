#ifndef PROGRAMMODE_H
#define PROGRAMMODE_H

#include <chrono>
#include "src/graphics/gui/PMIDGWindow.h"

class ProgramMode
{  
 public:
    virtual void Update(std::chrono::time_point<std::chrono::high_resolution_clock>& current_time) = 0;
    virtual void Render(float current_time) = 0;
    virtual void Exit() = 0;
    virtual void Init(){};
};
#endif