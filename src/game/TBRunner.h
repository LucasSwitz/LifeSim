#ifndef TBRUNNER_H
#define TBRUNNER_H

#include <chrono>
#include "src/utils/lua/LuaUniversal.h"
#include "src/utils/lua/LuaBindings.h"
#include "src/system/SystemFactory.h"
#include "src/event/EventSubscriber.h"
#include "src/event/EventType.h"
#include "src/game/mode/ProgramModeEditor.h"
#include "src/graphics/gui/TBWindow.h"

#define FRAMES_PER_SEC 30

/**
    Purpose: TBRunner handles the main operating loop of the program. Instances of TBRunner
             have a TBMode that will carry out operating procedures for the program. 
**/

class TBRunner : public EventSubscriber
{
  public:
    enum Type
    {
        GAME,
        EDITOR
    };

    TBRunner();

    void Init(Type type);

    void Run();

    void OnEvent(Event &e) override;

    std::list<Subscription> GetSubscriptions();

  private:
    ptr<ProgramMode> _mode = nullptr;
    bool _program_stopped = false;
    EventManager _program_event_manager;
};

#endif