#ifndef PROGRAMMODEEDITOR_H
#define PROGRAMMODEEDITOR_H

#include "src/game/mode/ProgramMode.h"
#include "src/game/gui/gui_tools/DevelopmentOverlay.h"
#include "src/system/SystemController.h"
#include "src/game/FPSRunner.h"
#include "src/game/gui/SFMLWindowListener.h"
#include "src/game/gui/PMIDGEditorWindow.h"
#include "src/game/gui/brush/Brush.h"
#include "src/utils/window/WindowUtils.h"

#define MAX_SCROLL_TICKS 50

class ProgramModeEditor : public ProgramMode, public SFMLWindowListener, public DevelopmentOverlayListener
{

  public:
    enum WindowTransformState
    {
        DORMANT,
        PANNING
    };

    ProgramModeEditor(PMIDGEditorWindow *window) : ProgramMode(window)
    {
        int current_mouse_position_x = sf::Mouse::getPosition(window->SFWindow()).x;

        LuaTileFactory::Instance()->PopulateFactory();

        _dev_tools.Init(window);
        _dev_tools.SetListener(this);
        _window->AddWindowListener(this);
    }

    void Update(float seconds_elapsed) override
    {
        _fps_runner.Update(seconds_elapsed);
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

    void PanView()
    {
        sf::Vector2i screen_mouse_position = sf::Mouse::getPosition(_window->SFWindow());

        int delta_x = screen_mouse_position.x - _mouse_history.x1;
        int delta_y = screen_mouse_position.y - _mouse_history.y1;

        _mouse_history.x1 = screen_mouse_position.x;
        _mouse_history.y1 = screen_mouse_position.y;
        static_cast<PMIDGEditorWindow *>(_window)->MoveView(-delta_x, -delta_y);
    }

    void OnSFEvent(sf::Event &event)
    {
        _fps_runner.OnSFEvent(event);
    }

    void Exit() override
    {
        _dev_tools.Shutdown();
    }

    void OnCreateBlankInstance(int rows, int columns) override
    {
        _active_instance = new Instance();
        TileMap map;

        map.Blank(rows, columns);
        _active_instance->SetTileMap(map);

        _fps_runner.SetRunnable(_active_instance);

        _active_instance->Open();

        static_cast<PMIDGEditorWindow *>(_window)->OnInstanceSizeChange(_active_instance->GetTileMap().WidthPx(),
                                                                        _active_instance->GetTileMap().HeightPx());
    }

    void OnCreateBlankStage()
    {
    }

    bool OnWindowEvent(sf::Event &e)
    {
        ImGui::SFML::ProcessEvent(e);

        if (!_dev_tools.IsFocused())
        {
            if (e.type == sf::Event::MouseButtonPressed || e.type == sf::Event::MouseButtonReleased)
            {
                if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Middle)
                {
                    sf::Vector2i pixelPos = sf::Vector2i(e.mouseButton.x, e.mouseButton.y);

                    _mouse_history.x1 = pixelPos.x;
                    _mouse_history.y1 = pixelPos.y;

                    _window_transform_state = PANNING;
                }
                else if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Middle)
                {
                    _window_transform_state = DORMANT;
                }
                else if (ClickOnActiveTileMap(e.mouseButton.x, e.mouseButton.y))
                {
                    sf::Vector2i pixel_pos = sf::Vector2i(e.mouseButton.x, e.mouseButton.y);
                    sf::Vector2f world_pos = _window->SFWindow().mapPixelToCoords(pixel_pos);

                    return _brush.OnInstanceMouseEvent(e, world_pos, _active_instance);
                }
            }
            else if (e.type == sf::Event::MouseWheelMoved)
            {
                _abs_scroll_ticks = _abs_scroll_ticks > 50 ? 50 : _abs_scroll_ticks - e.mouseWheel.delta;
                _abs_scroll_ticks = _abs_scroll_ticks < 0 ? 0 : _abs_scroll_ticks - e.mouseWheel.delta;

                static_cast<PMIDGEditorWindow *>(_window)->Zoom((float)_abs_scroll_ticks / (float)MAX_SCROLL_TICKS);
            }
        }
    }

    bool ClickOnActiveTileMap(int x, int y)
    {
        sf::Vector2f world_cords = _window->SFWindow().mapPixelToCoords(sf::Vector2i(x, y));
        return _active_instance && _active_instance->GetTileMap().TileAt(world_cords.x, world_cords.y);
    }

  private:
    FPSRunner _fps_runner;
    MouseHistory _mouse_history;
    DevelopmentOverlay _dev_tools;
    Instance *_active_instance = nullptr;
    int _abs_scroll_ticks = 50;
    Brush _brush;
    WindowTransformState _window_transform_state = DORMANT;
};

#endif