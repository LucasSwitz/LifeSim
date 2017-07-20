#ifndef PMIDGRUNNER_H
#define PMIDGRUNNER_H

#include <chrono>
#include "src/utils/lua/LuaUniversal.h"
#include "src/utils/lua/LuaBindings.h"
#include "src/system/SystemFactory.h"
#include "src/event/EventSubscriber.h"
#include "src/event/EventType.h"
#include "src/game/mode/ProgramModeEditor.h"
#include "src/game/gui/PMIDGWindow.h"

#define FRAMES_PER_SEC 30

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
        EventManager::Instance()->RegisterSubscriber(this);
    }

    void Init(Type type)
    {
        _last_time = std::chrono::time_point<std::chrono::high_resolution_clock>::min();


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
        if (_last_time == std::chrono::time_point<std::chrono::high_resolution_clock>::min())
            _last_time = std::chrono::high_resolution_clock::now();

        while (!_window_closed)
        {
            auto current_time = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> diff = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - _last_time);

            double seconds_elapsed_since_last_update = std::abs(diff.count());

            if (seconds_elapsed_since_last_update > (1.0 / (FRAMES_PER_SEC)))
            {
                if (_mode)
                {
                    _window->Clear();
                    _window->PollEvents();
                    _mode->Update(seconds_elapsed_since_last_update);
                    _window->Render();
                    _mode->Render(seconds_elapsed_since_last_update);
                    _window->Display();
                }

                _last_time = current_time;
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
    PMIDGWindow *_window;
    ProgramMode *_mode;
    std::chrono::time_point<std::chrono::high_resolution_clock> _last_time;
    bool _window_closed = false;
};

#endif