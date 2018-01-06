#ifndef PROGRAMMODE_H
#define PROGRAMMODE_H

#include <chrono>
#include "src/graphics/gui/TBWindow.h"
#include "src/event/EventManager.h"

class ProgramMode
{
  public:
    ProgramMode(EventManager& program_event_manager) : _program_event_manager(program_event_manager){};
    virtual void Update(std::chrono::time_point<std::chrono::high_resolution_clock> &current_time) = 0;
    virtual void Render(float current_time) = 0;
    virtual void Exit() = 0;
    virtual void Init(){};
  protected:
    EventManager& _program_event_manager;
};
#endif