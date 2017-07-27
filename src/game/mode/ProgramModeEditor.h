#ifndef PROGRAMMODEEDITOR_H
#define PROGRAMMODEEDITOR_H
#include <SFML/Graphics/CircleShape.hpp>

#include "src/graphics/gui/gui_tools/DevelopmentOverlay.h"
#include "src/graphics/gui/SFMLWindowListener.h"
#include "src/graphics/gui/PMIDGEditorWindow.h"
#include "src/graphics/gui/brush/Brush.h"
#include "src/graphics/gui/brush/SelectEntityBrushState.h"
#include "src/game/FPSRunner.h"
#include "src/game/GameState.h"
#include "src/game/mode/ProgramMode.h"
#include "src/game/control/GameLoader.h"
#include "src/utils/window/WindowUtils.h"
#include "src/utils/sfml/SFMLUtils.h"
#include "src/system/SystemController.h"

#define MAX_SCROLL_TICKS 50
#define EDITOR_MODE_FPS 30
#define GAME_RUNNER_FPS 30

class ProgramModeEditor : public ProgramMode, public SFMLWindowListener, public DevelopmentOverlayListener, public FPSRunner, public FPSRunnable
{

  public:
    enum WindowTransformState
    {
        DORMANT,
        PANNING
    };

    ProgramModeEditor(PMIDGEditorWindow *window) : ProgramMode(window), FPSRunner(EDITOR_MODE_FPS),
                                                   _editor_runner(EDITOR_MODE_FPS), _game_runner(GAME_RUNNER_FPS)
    {
        _game_state = new GameState();

        LuaTileFactory::Instance()->PopulateFactory();

        _dev_tools.Init(window);
        _dev_tools.SetListener(this);
        _window->AddWindowListener(this);

        _game_state->Setup();
        _game_runner.SetRunnable(_game_state);
        _editor_runner.SetRunnable(this);
    }

    void Load()
    {
    }

    void Update(std::chrono::time_point<std::chrono::high_resolution_clock> &current_time) override
    {
        _editor_runner.Update(current_time);
        _game_runner.Update(current_time);
    }

    void Tick(float seconds_elapsed)
    {
        _window->Clear();
        _window->PollEvents();
        _window->Render();
        Render(seconds_elapsed);
        _window->Display();
    }

    void Render(float seconds_elapsed) override
    {
        //chance to draw Dev Tools
        if (!_dev_tools.IsFocused())
        {
            if (_window_transform_state == PANNING)
            {
                PanView();
            }
            _brush.PaintWindow(*_window);
        }

        _dev_tools.Render(_window, _window->GetTextureCache(), seconds_elapsed, _brush);
    }

    void Unload()
    {
    }

    void PanView()
    {
        sf::Vector2i screen_mouse_position = sf::Mouse::getPosition(_window->SFWindow());

        int delta_x = screen_mouse_position.x - _mouse_history.x1;
        int delta_y = screen_mouse_position.y - _mouse_history.y1;

        _mouse_history.x1 = screen_mouse_position.x;
        _mouse_history.y1 = screen_mouse_position.y;
        static_cast<PMIDGEditorWindow *>(_window)->MoveView(-delta_x, -delta_y);
    }

    void Exit() override
    {
        _dev_tools.Shutdown();
    }

    void OnCreateBlankInstance(int rows, int columns) override
    {
        Instance *i = new Instance();
        _game_state->SetCurrentInstance(i);

        _game_state->GetInstance()->GetTileMap().Blank(10, 10);

        _game_state->GetInstance()->Open();

        static_cast<PMIDGEditorWindow *>(_window)->OnInstanceSizeChange(_game_state->GetInstance()->GetTileMap().WidthPx(),
                                                                        _game_state->GetInstance()->GetTileMap().HeightPx());
    }

    void OnCreateBlankStage()
    {
    }

    bool OnWindowEvent(sf::Event &e)
    {
        ImGui::SFML::ProcessEvent(e);

        if (!_dev_tools.IsFocused())
        {
            sf::Vector2i pixel_pos = sf::Vector2i(e.mouseButton.x, e.mouseButton.y);
            sf::Vector2f world_pos = _window->SFWindow().mapPixelToCoords(pixel_pos);

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
                    if (Entity *entity = ClickOnEntity(pixel_pos.x, pixel_pos.y))
                    {
                        if (e.type == sf::Event::MouseButtonPressed)
                        {
                            _brush.SetState(new SelectEntityBrushState(entity));
                        }

                        if(_brush.OnInstanceMouseEvent(e, world_pos, _game_state->GetInstance()))
                        {
                            _brush.SetState(nullptr);
                        }
                    }
                }
                else if (e.type == sf::Event::MouseWheelMoved)
                {
                    _abs_scroll_ticks = _abs_scroll_ticks > 50 ? 50 : _abs_scroll_ticks - e.mouseWheel.delta;
                    _abs_scroll_ticks = _abs_scroll_ticks < 0 ? 0 : _abs_scroll_ticks - e.mouseWheel.delta;

                    static_cast<PMIDGEditorWindow *>(_window)->Zoom((float)_abs_scroll_ticks / (float)MAX_SCROLL_TICKS);
                }
                else if (e.type == sf::Event::KeyPressed)
                {
                    _brush.OnKeyboardEvent(e, _game_state->GetInstance());
                }
            }
        }
    }

    void OnSFEvent(sf::Event &event)
    {
    }

    bool ClickOnActiveTileMap(int x, int y)
    {
        sf::Vector2f world_cords = _window->SFWindow().mapPixelToCoords(sf::Vector2i(x, y));
        return _game_state->GetInstance() && _game_state->GetInstance()->GetTileMap().TileAt(world_cords.x, world_cords.y);
    }

    Entity *ClickOnEntity(int x, int y)
    {
        sf::Vector2f world_pos = _window->SFWindow().mapPixelToCoords(sf::Vector2i(x, y));

        std::map<int, Entity *> &entities = EntityManager::Instance()->GetAllEntities();

        for (auto it = entities.begin(); it != entities.end(); it++)
        {
            Entity *e = it->second;

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

    void OnLoadGameStateFile(const std::string &file_name) override
    {
        if (_game_state)
            delete _game_state;

        _brush.SetState(nullptr);
        _game_state = new GameState();
        _game_state->Setup();
        _game_runner.SetRunnable(_game_state);

        GameLoader loader;
        loader.Load(file_path, file_name, *_game_state);

        static_cast<PMIDGEditorWindow *>(_window)->OnInstanceSizeChange(_game_state->GetInstance()->GetTileMap().WidthPx(),
                                                                        _game_state->GetInstance()->GetTileMap().HeightPx());
    }

    void OnSaveGameStateFile(const std::string &file_name) override
    {
        if (_game_state && _game_state->GetInstance())
        {
            _game_state->GetInstance()->GetTileMap()
                .SaveToFile(tile_maps_path + "/" + std::to_string(_game_state->GetInstance()->GetID()) + ".pmidgM");
            GameLoader loader;
            loader.Save(file_path, file_name, *_game_state);
        }
    }

  private:
    FPSRunner _game_runner;
    FPSRunner _editor_runner;
    MouseHistory _mouse_history;
    DevelopmentOverlay _dev_tools;
    int _abs_scroll_ticks = 50;
    Brush _brush;
    GameState *_game_state;
    WindowTransformState _window_transform_state = DORMANT;
    std::string file_path = "/home/pabu/Desktop/LifeSim/build/instances";
    std::string tile_maps_path = "/home/pabu/Desktop/LifeSim/res/tile_maps";
};

#endif