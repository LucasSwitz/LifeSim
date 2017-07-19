#ifndef PROGRAMMODEEDITOR_H
#define PROGRAMMODEEDITOR_H

#include "src/game/mode/ProgramMode.h"
#include "src/game/gui/gui_tools/DevelopmentOverlay.h"
#include "src/system/SystemController.h"
#include "src/game/FPSRunner.h"
#include "src/game/gui/SFMLWindowListener.h"
#include "src/game/gui/PMIDGEditorWindow.h"
#include "src/game/gui/brush/Brush.h"
#include "src/game/gui/brush/SelectEntityBrushState.h"
#include "src/utils/window/WindowUtils.h"
#include "src/utils/sfml/SFMLUtils.h"
#include <SFML/Graphics/CircleShape.hpp>

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
        delete _active_instance;
        
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
                    if(e.type == sf::Event::MouseButtonPressed)
                    {
                        if(Entity *entity = ClickOnEntity(pixel_pos.x, pixel_pos.y))
                            _brush.SetState(new SelectEntityBrushState(entity));
                    }
                    _brush.OnInstanceMouseEvent(e, world_pos, _active_instance);
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

    Entity* ClickOnEntity(int x, int y)
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


            sf::Vector2f top_edge = corner_top_right - corner_top_left; //AB
            sf::Vector2f right_edge = corner_bot_right - corner_top_right; //BC

            sf::Vector2f top_left_to_click = world_pos - corner_top_left; //AM
            sf::Vector2f top_right_to_click = world_pos - corner_top_right; //BM


            float dot_top_click = sf::Dot(top_edge,top_left_to_click);     
            float dot_top_top = sf::Dot(top_edge,top_edge);
            float dot_right_click = sf::Dot(right_edge,top_right_to_click);     
            float dot_right_right = sf::Dot(right_edge,right_edge);     
     
            if(0 <= dot_top_click && dot_top_click <= dot_top_top && 
               0 <= dot_right_click && dot_right_click <= dot_right_right)
            {
                return e;
            }
        }
        return nullptr;
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