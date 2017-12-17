#include "src/game/mode/ProgramModeEditor.h"

ProgramModeEditor::ProgramModeEditor() : FPSRunner(EDITOR_MODE_FPS),
                                         _editor_runner(EDITOR_MODE_FPS),
                                         _game_runner(GAME_RUNNER_FPS),
                                         file_path(Globals::RESOURCE_ROOT + "/world/stages"),
                                         tile_maps_path(Globals::RESOURCE_ROOT + "/world/tile_maps"),
                                         instances_path(Globals::RESOURCE_ROOT + "/world/instances")
{
    _game_state = ptr<GameState>(new GameState());

    LuaTileFactory::Instance()->PopulateFactory(Globals::RESOURCE_ROOT);
    LuaInstanceFactory::Inst()->PopulateFactory(Globals::RESOURCE_ROOT);
    EngineEventManager::Instance()->RegisterSubscriber(this);

    _dev_tools.Init(_window);
    _dev_tools.SetListener(this);
    _window.AddWindowListener(this);

    _game_state->Setup();
    _game_runner.SetRunnable(_game_state);
    _game_state->GetMessageDispatch().RegisterSubscriber(this);
}

void ProgramModeEditor::Init()
{
    _editor_runner.SetRunnable(shared_from_this());
}

void ProgramModeEditor::Load()
{
    _window.Focus();
}

void ProgramModeEditor::Update(std::chrono::time_point<std::chrono::high_resolution_clock> &current_time)
{
    _editor_runner.Update(current_time);

    if (_external_game_runner)
        _external_game_runner->Update(current_time);
    else
    {
        _game_runner.Update(current_time);
    }
}

void ProgramModeEditor::Tick(float seconds_elapsed)
{
    _controllers_system.Update(seconds_elapsed, _game_state);
    _window.Clear();
    _window.PollEvents();
    _window.Render();
    Render(seconds_elapsed);
    _window.Display();
}

void ProgramModeEditor::Unload()
{
}

void ProgramModeEditor::Exit()
{
    _dev_tools.Shutdown();
}

//######################### DEV TOOL CALLBACKS ########################

void ProgramModeEditor::OnCreateBlankInstance(std::string &instance_name, int rows, int columns)
{

    TileMap map;
    TileMap::Blank(map, rows, columns);
    ptr<Instance> i(new Instance(-1, instance_name));
    i->SetTileMap(map);

    _game_state->GetStage()->AddInstance(i);

    GenerateInstanceTemplate(i);

    _window.OnInstanceSizeChange(i->GetTileMap().WidthPx(),
                                 i->GetTileMap().HeightPx());
}

void ProgramModeEditor::OnCreateBlankStage()
{
    _game_state = std::make_shared<GameState>();
    _game_state->Setup();
    _game_state->GetMessageDispatch().RegisterSubscriber(this);

    _game_runner.SetRunnable(_game_state);

    _game_state->SetStage(std::make_shared<LuaStage>());

    _window.SetName("New Stage Name");
}

void ProgramModeEditor::OnLaunchInstance()
{
    _external_game_runner = ptr<PMIDGGameRunner>(new PMIDGGameRunner());
    _external_game_runner->SetListener(this);
    _external_game_runner->RunGameState(*_game_state);
    _editor_runner.SetRunnable(_external_game_runner);
}

void ProgramModeEditor::OnLaunchStage()
{
}

void ProgramModeEditor::OnStopGameRunner()
{
    _game_state->Setup();
    _external_game_runner = nullptr;
    _editor_runner.SetRunnable(ptr<FPSRunnable>(this));
    _window.Focus();
}

void ProgramModeEditor::OnGameRunnerShutdown()
{
    OnStopGameRunner();
}

//###################### ENGINE EVENTS ################################
void ProgramModeEditor::OnEvent(Event &e)
{
    if (e.id == EventType::CLOSE_WINDOW_EVENT)
    {
        if (e.sender_id == _window.ID())
        {
            Event e = Event(EventType::STOP_PROGRAM_EVENT, -1, -1);
            EngineEventManager::Instance()->LaunchEvent(e);
        }
    }
    if (e.id == EventType::STAGE_INSTANCE_CHANGED)
    {
        ptr<Instance> current_instance = _game_state->GetStage()->GetCurrentInstance();

        _window.OnInstanceSizeChange(current_instance->GetTileMap().WidthPx(),
                                     current_instance->GetTileMap().HeightPx());
    }
    if (e.id == EventType::STAGE_INSTANCE_CHANGING)
    {
        ptr<Instance> current_instance = _game_state->GetStage()->GetCurrentInstance();
        if (current_instance)
            SaveInstanceTilemap(current_instance);
    }
}

std::list<Subscription> ProgramModeEditor::GetSubscriptions()
{
    std::list<Subscription> subs = {Subscription(EventType::CLOSE_WINDOW_EVENT),
                                    Subscription(EventType::STAGE_INSTANCE_CHANGING),
                                    Subscription(EventType::STAGE_INSTANCE_CHANGED)};
    return subs;
}

// ######################## LOADING / SAVING #################################
void ProgramModeEditor::OnLoadStageFile(const std::string &file_name)
{
    _game_state = ptr<GameState>(new GameState());
    _game_state->Setup();
    _game_state->GetMessageDispatch().RegisterSubscriber(this);

    GameLoader loader;
    loader.Load(file_path, file_name, *_game_state);

    _game_runner.SetRunnable(_game_state);
}

void ProgramModeEditor::OnSaveStageFile(const std::string &file_name)
{
    if (_game_state && _game_state->GetStage())
    {
        ptr<Stage> stage = _game_state->GetStage();

        if (stage->GetCurrentInstance())
            SaveInstanceTilemap(stage->GetCurrentInstance());
        stage->SetName(file_name);

        GameLoader loader;
        loader.Save(file_path, file_name, *_game_state);
    }
}

void ProgramModeEditor::SaveInstanceTilemap(ptr<Instance> instance)
{
    std::string tile_map_path = tile_maps_path + "/" + instance->GetName() + ".pmidgM";
    instance->GetTileMap().SaveToFile(tile_map_path);
}

void ProgramModeEditor::GenerateInstanceTemplate(ptr<Instance> instance)
{
    SaveInstanceTilemap(instance);

    InstanceFileBuilder instance_builder(instance->GetName(), instance->GetID());

    instance_builder.SetTilemapFile(instance->GetTileMap().GetFile());

    std::string instance_path = instances_path + "/" + instance->GetName() + ".pmidgI";
    instance_builder.Output(instance_path);

    LuaInstanceFactory::Inst()->AddScript(instance->GetName(), instance->GetID(), instance_path);
}

bool ProgramModeEditor::OnWindowEvent(sf::Event &e)
{
    ImGui::SFML::ProcessEvent(e);

    if (!_dev_tools.IsFocused())
    {
        sf::Vector2i pixel_pos = sf::Vector2i(e.mouseButton.x, e.mouseButton.y);
        sf::Vector2f world_pos = _window.SFWindow().mapPixelToCoords(pixel_pos);

        if (e.type == sf::Event::MouseButtonPressed || e.type == sf::Event::MouseButtonReleased)
        {
            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Middle)
            {
                sf::Vector2i pixelPos = sf::Vector2i(e.mouseButton.x, e.mouseButton.y);

                _mouse_history.x1 = pixelPos.x;
                _mouse_history.y1 = pixelPos.y;

                _window_transform_state = PANNING;
            }
            else if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Middle)
            {
                _window_transform_state = DORMANT;
            }
            else if (ClickOnActiveTileMap(e.mouseButton.x, e.mouseButton.y))
            {
                if (ptr<Entity> entity = ClickOnEntity(pixel_pos.x, pixel_pos.y))
                {
                    if (e.type == sf::Event::MouseButtonPressed)
                    {
                        _brush.SetState(ptr<BrushState>(new SelectEntityBrushState(entity)));
                    }
                    _brush.OnGameStateMouseEvent(e, world_pos, _game_state, entity);
                }
                else
                {
                    _brush.OnGameStateMouseEvent(e, world_pos, _game_state);
                }
            }
        }
        else if (e.type == sf::Event::MouseWheelMoved)
        {
            _abs_scroll_ticks = _abs_scroll_ticks > 50 ? 50 : _abs_scroll_ticks - e.mouseWheel.delta;
            _abs_scroll_ticks = _abs_scroll_ticks < 0 ? 0 : _abs_scroll_ticks - e.mouseWheel.delta;

            _window.Zoom((float)_abs_scroll_ticks / (float)MAX_SCROLL_TICKS);
        }
        else if (e.type == sf::Event::KeyPressed)
        {
            _brush.OnKeyboardEvent(e, _game_state);
        }
    }
}

//################ SCREEN CONTROLS #################

void ProgramModeEditor::Render(float seconds_elapsed)
{
    //chance to draw Dev Tools
    if (!_dev_tools.IsFocused())
    {
        if (_window_transform_state == PANNING)
        {
            PanView();
        }
    }
    _dev_tools.Render(_window, _game_state, _window.GetTextureCache(), seconds_elapsed, _brush);
}

void ProgramModeEditor::PanView()
{
    sf::Vector2i screen_mouse_position = sf::Mouse::getPosition(_window.SFWindow());

    int delta_x = screen_mouse_position.x - _mouse_history.x1;
    int delta_y = screen_mouse_position.y - _mouse_history.y1;

    _mouse_history.x1 = screen_mouse_position.x;
    _mouse_history.y1 = screen_mouse_position.y;
    _window.MoveView(-delta_x, -delta_y);
}

bool ProgramModeEditor::ClickOnActiveTileMap(int x, int y)
{
    if (!CanEdit())
        return false;

    ptr<Instance> instance = _game_state->GetStage()->GetCurrentInstance();
    sf::Vector2f world_cords = _window.SFWindow().mapPixelToCoords(sf::Vector2i(x, y));
    return (instance->GetTileMap().TileAt(world_cords.x, world_cords.y)) != nullptr;
}

ptr<Entity> ProgramModeEditor::ClickOnEntity(int x, int y)
{
    if (!CanEdit())
        return nullptr;

    sf::Vector2f world_pos = _window.SFWindow().mapPixelToCoords(sf::Vector2i(x, y));

    auto entities = _game_state->GetEntityManager().GetAllEntities();

    for (auto it = entities.begin(); it != entities.end(); it++)
    {
        ptr<Entity> e = it->second;

        int pos_x = e->GetComponentValueFloat("Position", "x");
        int pos_y = e->GetComponentValueFloat("Position", "y");

        int width = 0;
        int height = 0;

        if (e->HasComponent("Collision"))
        {
            width = e->GetComponentValueFloat("Collision", "width");
            height = e->GetComponentValueFloat("Collision", "height");
        }
        else if (e->HasComponent("Graphics"))
        {
            width = e->GetComponentValueFloat("Graphics", "width");
            height = e->GetComponentValueFloat("Graphics", "height");
        }
        else
        {
            continue;
        }

        sf::Vector2f corner_top_left(pos_x - width / 2.0, pos_y - height / 2.0);
        sf::Vector2f corner_top_right(pos_x + width / 2.0, pos_y - height / 2.0);
        sf::Vector2f corner_bot_right(pos_x + width / 2.0, pos_y + height / 2.0);

        sf::Vector2f top_edge = corner_top_right - corner_top_left;    //AB
        sf::Vector2f right_edge = corner_bot_right - corner_top_right; //BC

        sf::Vector2f top_left_to_click = world_pos - corner_top_left;   //AM
        sf::Vector2f top_right_to_click = world_pos - corner_top_right; //BM

        float dot_top_click = sf::Dot(top_edge, top_left_to_click);
        float dot_top_top = sf::Dot(top_edge, top_edge);
        float dot_right_click = sf::Dot(right_edge, top_right_to_click);
        float dot_right_right = sf::Dot(right_edge, right_edge);

        if (0 <= dot_top_click && dot_top_click <= dot_top_top &&
            0 <= dot_right_click && dot_right_click <= dot_right_right)
        {
            return e;
        }
    }
    return nullptr;
}

bool ProgramModeEditor::CanEdit()
{
    return _game_state && _game_state->GetStage() && _game_state->GetStage()->GetCurrentInstance();
}
