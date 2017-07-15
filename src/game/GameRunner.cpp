#include "GameRunner.h"

GameRunner::GameRunner()
{
    
}

void GameRunner::Init()
{
    LuaUniversal::Instance()->Init();
    SystemController::Instance()->Reset();
    SystemFactory::Instance()->PopulateFactory();
    LuaTileFactory::Instance()->PopulateFactory();

    _initialized = true;
}

bool GameRunner::Initialized()
{
    return _initialized;
}

void GameRunner::Shutdown()
{
    
}

void GameRunner::Update(float seconds_elapsed)
{
    UpdateSystems(seconds_elapsed); //<---- move these to a higher-level class
    UpdateStage(seconds_elapsed);
}

int GameRunner::UpdateStage(float time)
{
    if(_current_stage)
        _current_stage->Update(time);
}

void GameRunner::ChangeStage(Stage* stage)
{
    if(_current_stage)
        _current_stage->Exit();

    _current_stage = stage;

    //load the current stages resources (loading screen?)

    if(_current_stage)
        _current_stage->Enter();
    else
        return;//bad stage
}

int GameRunner::UpdateSystems(float time)
{
    SystemController::Instance()->Update(time);
    return 0;
}

void GameRunner::OnEvent(Event& e)
{
    if(e.id == EventType::EXIT_STAGE_EVENT)
    {
        int stage_id = *(e.InfoToType<int*>());
        ChangeStage(LuaStageFactory::Instance()->GetStage(stage_id));
    }
}

Stage* GameRunner::GetCurrentStage()
{
    return _current_stage;
}

std::list<Subscription> GameRunner::GetSubscriptions()
{
    std::list<Subscription> subs = {Subscription(EventType::EXIT_STAGE_EVENT)};

    return subs;
}