#ifndef PROGRAMMODEEDITOR_H
#define PROGRAMMODEEDITOR_H

#include "src/game/mode/ProgramMode.h"
#include "src/game/gui/gui_tools/DevelopmentOverlay.h"
#include "src/system/SystemController.h"
#include "src/game/FPSRunner.h"
#include "src/game/gui/SFMLWindowListener.h"
#include "src/game/gui/PMIDGEditorWindow.h"

#define MAX_SCROLL_TICKS 50

class ProgramModeEditor : public ProgramMode, public SFMLWindowListener, public DevelopmentOverlayListener
{
  public:
    struct PaintStruct
    {
        int x1;
        int x2;
        int y1;
        int y2;
    };

    struct MouseHistory
    {
        int x1;
        int x2;
        int y1;
        int y2;
    };

    enum PaintingEditState
    {
        DORMANT,
        PAINTING,
        PANNING,
    };

    ProgramModeEditor(PMIDGEditorWindow *window) : ProgramMode(window)
    {
        int current_mouse_position_x = sf::Mouse::getPosition(window->SFWindow()).x;

        SystemController::Instance()->AddToSystemExecutionSequence("DrawGraphicsSystem");
        LuaTileFactory::Instance()->PopulateFactory();

        _dev_tools.Init(window);
        _dev_tools.SetListener(this);
        //_dev_tools.SetNewCreateableListener(this);
        _window->AddWindowListener(this);
    }

    void Update(float seconds_elapsed) override 
    {
        _fps_runner.Update(seconds_elapsed);
    }

    void Render(float seconds_elapsed) override
    {
        //chance to draw Dev Tools
        if (_painting_state == PAINTING)
        {
            RenderSelectBox();
        }
        else if(_painting_state == PANNING)
        {
            PanView();
        }

        _dev_tools.Render(_window, _window->GetTextureCache(), seconds_elapsed);
    }

    void RenderSelectBox()
    {
        sf::Vector2i screen_mouse_position = sf::Mouse::getPosition(_window->SFWindow());
        sf::Vector2f world_mouse_position = _window->SFWindow().mapPixelToCoords(screen_mouse_position);

        int current_mouse_position_x = world_mouse_position.x;
        int current_mouse_position_y = world_mouse_position.y;

        int delta_x = current_mouse_position_x - _paint_struct.x1;
        int delta_y = current_mouse_position_y - _paint_struct.y1;

        int width = std::abs(delta_x);
        int height = std::abs(delta_y);

        int pos_x = (delta_x < 0 ? current_mouse_position_x : _paint_struct.x1);
        int pos_y = (delta_y < 0 ? current_mouse_position_y : _paint_struct.y1);

        sf::RectangleShape rect(sf::Vector2f(width, height));
        rect.setPosition(pos_x,pos_y);
        _window->DrawNow(rect);
    }

    void PanView()
    {
        sf::Vector2i screen_mouse_position = sf::Mouse::getPosition(_window->SFWindow());

        int delta_x = screen_mouse_position.x - _paint_struct.x1;
        int delta_y = screen_mouse_position.y - _paint_struct.y1;

        _paint_struct.x1 = screen_mouse_position.x;
        _paint_struct.y1 = screen_mouse_position.y;
        std::cout << delta_x << " , " <<  delta_y << std::endl;
        static_cast<PMIDGEditorWindow*>(_window)->MoveView(-delta_x, -delta_y);
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

        static_cast<PMIDGEditorWindow*>(_window)->OnInstanceSizeChange(_active_instance->GetTileMap().WidthPx(), 
                                                                       _active_instance->GetTileMap().HeightPx());
    }

    enum ClickState
    {
        NO_CLICK,
        SINGLE_PAINT,
        FREE_PAINT,
        BLOCK_PAINTnullptr
    };

    void OnCreateBlankStage()
    {
    }

    bool OnWindowEvent(sf::Event &e)
    {
        ImGui::SFML::ProcessEvent(e);

        if (ClickOnActiveTileMap(e.mouseButton.x, e.mouseButton.y))
        {
            if (e.type == sf::Event::MouseButtonPressed)
            {
                if (e.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i pixelPos = sf::Vector2i(e.mouseButton.x, e.mouseButton.y);

                    sf::Vector2f worldPos = _window->SFWindow().mapPixelToCoords(pixelPos);

                    _paint_struct.x1 = worldPos.x;
                    _paint_struct.y1 = worldPos.y;
                    _painting_state = PAINTING;
                }
                else if (e.mouseButton.button == sf::Mouse::Right)
                {
                    _painting_state = DORMANT;
                }
                else if(e.mouseButton.button = sf::Mouse::Middle)
                {
                    sf::Vector2i pixelPos = sf::Vector2i(e.mouseButton.x, e.mouseButton.y);

                    _paint_struct.x1 = pixelPos.x;
                    _paint_struct.y1 = pixelPos.y;

                    _painting_state = PANNING;
                }
            }
            else if (e.type == sf::Event::MouseButtonReleased)
            {
                if (_painting_state == PAINTING && e.mouseButton.button == sf::Mouse::Left)
                {

                    sf::Vector2i pixelPos = sf::Vector2i(e.mouseButton.x, e.mouseButton.y);
                    sf::Vector2f worldPos = _window->SFWindow().mapPixelToCoords(pixelPos);

                    _paint_struct.x2 = worldPos.x;
                    _paint_struct.y2 = worldPos.y;

                    std::list<Tile *> boxed_tiles;
                    _active_instance->GetTileMap().TilesInRange(_paint_struct.x1, _paint_struct.y1,
                                                                _paint_struct.x2, _paint_struct.y2,
                                                                boxed_tiles);

                    std::string new_texture_path = _dev_tools.tile_map_editor.GetSelectedTexturePath();

                    if (!new_texture_path.empty())
                    {
                        for (Tile *boxed_tile : boxed_tiles)
                            boxed_tile->SetComponentValueString("Graphics", "sprite", new_texture_path);
                    }
                }
                _painting_state = DORMANT;
            }
            else if(e.type == sf::Event::MouseWheelMoved)
            {
                _abs_scroll_ticks = _abs_scroll_ticks > 50 ? 50 : _abs_scroll_ticks-e.mouseWheel.delta;
                _abs_scroll_ticks = _abs_scroll_ticks < 0 ? 0 : _abs_scroll_ticks-e.mouseWheel.delta;

                static_cast<PMIDGEditorWindow*>(_window)->Zoom((float)_abs_scroll_ticks / (float)MAX_SCROLL_TICKS);
            }
            return true;
        }
    }

    bool ClickOnActiveTileMap(int x, int y)
    {
        sf::Vector2f world_cords = _window->SFWindow().mapPixelToCoords(sf::Vector2i(x,y));
        return _active_instance && _active_instance->GetTileMap().TileAt(world_cords.x, world_cords.y);
    }

  private:
    FPSRunner _fps_runner;
    DevelopmentOverlay _dev_tools;
    Instance *_active_instance = nullptr;
    PaintStruct _paint_struct;
    PaintingEditState _painting_state = DORMANT;
    int _abs_scroll_ticks = 50;
    MouseHistory _mouse_history;
};

#endif