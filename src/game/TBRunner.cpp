#include "src/game/TBRunner.h"

TBRunner::TBRunner()
{
    LuaUniversal::Instance()->Init();
    LuaBindings::Bind(LUA_STATE);
    LuaEntityFactory::Instance()->PopulateFactory(Globals::RESOURCE_ROOT);
    SystemFactory::Instance()->PopulateFactory(Globals::RESOURCE_ROOT);
    _program_event_manager.RegisterSubscriber(this);
}

void TBRunner::Init(Type type)
{
    switch (type)
    {
    case EDITOR:
        _mode = std::make_shared<ProgramModeEditor>(_program_event_manager);
        _mode->Init();
        break;
    case GAME:
        break;
    }
}

void TBRunner::Run()
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

void TBRunner::OnEvent(Event &e)
{
    if (e.id == EventType::STOP_PROGRAM_EVENT)
    {
        _program_stopped = true;
    }
}

std::list<Subscription> TBRunner::GetSubscriptions()
{
    std::list<Subscription> list = {Subscription(EventType::STOP_PROGRAM_EVENT)};
    return list;
}
