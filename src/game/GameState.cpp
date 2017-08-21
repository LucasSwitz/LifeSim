#include "src/game/GameState.h"

GameState::GameState()
{
    _message_dispatch.RegisterSubscriber(&_system_controller);
    _component_users.AddSubscriber(&_player_base, "Player");
}

GameState::GameState(const GameState &game_state) : _message_dispatch(),
                                                    _entity_manager(game_state._entity_manager, _component_users),
                                                    _system_controller(game_state._system_controller),
                                                    _current_stage(game_state._current_stage)
{
    _message_dispatch.RegisterSubscriber(&_system_controller);
    _component_users.AddSubscriber(&_player_base, "Player");
    //all the things need to add themselves to the component user base
}

void GameState::Load()
{
}

void GameState::Setup()
{
    MessageDispatch::GiveOwnership(&_message_dispatch);
    ComponentUserBase::GiveOwnership(&_component_users);
    EntityManager::GiveOwnership(&_entity_manager);
    SystemController::GiveOwnership(&_system_controller);
}

void GameState::Tick(float seconds_elapsed)
{

    if (_current_stage && _current_stage->GetCurrentInstance())
    {
        _system_controller.Update(seconds_elapsed);
        _current_stage->Tick(seconds_elapsed);
    }

    _entity_manager.Clean();

    //if using lua
    LuaUniversal::Instance()->CollectGarbage();
}

void GameState::Unload()
{
}

void GameState::SetStage(Stage *stage)
{
    _current_stage = stage;
    _current_stage->Load();
    _current_stage->Enter();
}

void GameState::ChangeState(Stage *new_stage)
{
    if (_current_stage)
    {
        _current_stage->Exit();
        _current_stage->Unload();
    }

    SetStage(new_stage);
}

void GameState::AddSystem(std::string system_name)
{
    _system_controller.AddToSystemExecutionSequence(system_name);
}

void GameState::AddSystem(System *system)
{
    _system_controller.AddToSystemExecutionSequence(system);
}

void GameState::AddEntity(Entity *e)
{
    if (e->GetInstance() != -1)
    {
        Instance *i = _current_stage->GetInstance(e->GetInstance());
        i->AddLocalEntity(e->ID());
        _entity_manager.RegisterEntity(e);
    }
    else
    {
        std::cout << "Entity has no instance...can't add" << std::endl;
    }
}

Stage *GameState::GetStage()
{
    return _current_stage;
}

EntityManager &GameState::GetEntityManager()
{
    return _entity_manager;
}

ComponentUserBase &GameState::GetComponentUserBase()
{
    return _component_users;
}

SystemController &GameState::GetSystemController()
{
    return _system_controller;
}
