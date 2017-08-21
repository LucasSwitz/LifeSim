#include "src/game/PMIDGRunner.h"

PMIDGRunner::PMIDGRunner()
{
    LuaUniversal::Instance()->Init();
    LuaBindings::Bind(LUA_STATE);
    LuaEntityFactory::Instance()->PopulateFactory();
    SystemFactory::Instance()->PopulateFactory();
    EngineEventManager::GiveOwnership(&_event_manager);
    EngineEventManager::Instance()->RegisterSubscriber(this);
}

void PMIDGRunner::Init(Type type)
{
    switch (type)
    {
    case EDITOR:
        _mode = new ProgramModeEditor();
        break;
    case GAME:
        break;
    }
}

void PMIDGRunner::Run()
{
    while (!_program_stopped)
    {
        if (_mode)
        {
            std::chrono::time_point<std::chrono::high_resolution_clock> current_time = std::chrono::high_resolution_clock::now();
            _mode->Update(current_time);
        }
    }
}

void PMIDGRunner::OnEvent(Event &e)
{
    if (e.id == EventType::STOP_PROGRAM_EVENT)
    {
        _program_stopped = true;
    }
}

std::list<Subscription> PMIDGRunner::GetSubscriptions()
{
    std::list<Subscription> list = {Subscription(EventType::STOP_PROGRAM_EVENT)};
    return list;
}
