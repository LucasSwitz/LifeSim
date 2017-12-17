#ifndef PMIDGRUNNER_H
#define PMIDGRUNNER_H

#include <chrono>
#include "src/utils/lua/LuaUniversal.h"
#include "src/utils/lua/LuaBindings.h"
#include "src/system/SystemFactory.h"
#include "src/event/EventSubscriber.h"
#include "src/event/EventType.h"
#include "src/game/mode/ProgramModeEditor.h"
#include "src/graphics/gui/PMIDGWindow.h"

#define FRAMES_PER_SEC 30

/**
    Purpose: PMIDGRunner handles the main operating loop of the program. Instances of PMIDGRunner
             have a PMIDGMode that will carry out operating procedures for the program. 
**/

class PMIDGRunner : public EventSubscriber
{
  public:
    enum Type
    {
        GAME,
        EDITOR
    };

    PMIDGRunner();

    void Init(Type type);

    void Run();

    void OnEvent(Event &e) override;

    std::list<Subscription> GetSubscriptions();

  private:
    ptr<ProgramMode> _mode = nullptr;
    bool _program_stopped = false;
};

#endif