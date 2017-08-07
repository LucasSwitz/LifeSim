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

    PMIDGRunner()
    {
        LuaUniversal::Instance()->Init();
        LuaBindings::Bind(LUA_STATE);
        LuaEntityFactory::Instance()->PopulateFactory();
        SystemFactory::Instance()->PopulateFactory();
        EngineEventManager::GiveOwnership(&_event_manager);
        EngineEventManager::Instance()->RegisterSubscriber(this);
    }

    void Init(Type type)
    {
        switch (type)
        {
        case EDITOR:
            _window = new PMIDGEditorWindow();
            _mode = new ProgramModeEditor(static_cast<PMIDGEditorWindow *>(_window));
            break;
        case GAME:
            break;
        }
    }

    void Run()
    {
        while (!_window_closed)
        {
            if (_mode)
            {
                std::chrono::time_point<std::chrono::high_resolution_clock> current_time = std::chrono::high_resolution_clock::now();
                _mode->Update(current_time);
            }
        }
    }

    void OnEvent(Event &e) override
    {
        if (e.id == EventType::CLOSE_GAME_WINDOW_EVENT)
        {
            _window_closed = true;
        }
    }

    std::list<Subscription> GetSubscriptions()
    {
        std::list<Subscription> list = {Subscription(EventType::CLOSE_GAME_WINDOW_EVENT)};
        return list;
    }

  private:
    PMIDGWindow *_window = nullptr;
    ProgramMode *_mode = nullptr;
    EngineEventManager _event_manager;
    bool _window_closed = false;
};

#endif