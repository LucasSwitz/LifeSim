#ifndef PROGRAMMODEEDITOR_H
#define PROGRAMMODEEDITOR_H

#include "src/game/mode/ProgramMode.h"
#include "src/game/gui/gui_tools/DevelopmentOverlay.h"
#include "src/system/SystemController.h"
#include "src/game/FPSRunner.h"
#include "src/game/gui/SFMLWindowListener.h"

class ProgramModeEditor : public ProgramMode, public SFMLWindowListener, public TileMapEditorListener
{
  public:
    struct PaintStruct
    {
        int x1;
        int x2;
        int y1;
        int y2;
    };

    enum PaintingEditState
    {
        DORMANT,
        PAINTING
    };

    ProgramModeEditor()
    {

    }

    void Init(PMIDGWindow &window)
    {
        int current_mouse_position_x = sf::Mouse::getPosition(window.SFWindow()).x;
        SystemController::Instance()->AddToSystemExecutionSequence("DrawGraphicsSystem");
        LuaTileFactory::Instance()->PopulateFactory();

        _dev_tools.Init(window);
        _dev_tools.SetTileMapEditorListener(this);
        //_dev_tools.SetNewCreateableListener(this);
        window.AddWindowListener(this);
    }

    void Update(float seconds_elapsed) override
    {
        _fps_runner.Update(seconds_elapsed);
    }

    void Render(PMIDGWindow &window, float seconds_elapsed) override
    {
        //chance to draw Dev Tools
        _dev_tools.Render(window, window.GetTextureCache(), seconds_elapsed);

        if(_painting_state == PAINTING)
        {
            RenderSelectBox(window);
        }
    }

    void RenderSelectBox(PMIDGWindow& window)
    {
        int current_mouse_position_x = sf::Mouse::getPosition(window.SFWindow()).x;
        int current_mouse_position_y = sf::Mouse::getPosition(window.SFWindow()).y;

        int delta_x  =  current_mouse_position_x - _paint_struct.x1;
        int delta_y  =  current_mouse_position_y - _paint_struct.y1;

        int width = std::abs(delta_x);
        int height = std::abs(delta_y);

        int pos_x = (delta_x < 0 ? current_mouse_position_x : _paint_struct.x1);
        int pos_y = (delta_y < 0 ? current_mouse_position_y : _paint_struct.y1);

        sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(width,height));
        rect->setPosition(pos_x,pos_y);
        window.Draw(rect);
    }

    void OnSFEvent(sf::Event &event)
    {
        _fps_runner.OnSFEvent(event);
    }

    void Exit() override
    {
        _dev_tools.Shutdown();
    }

    void OnCreateBlankInstance(int width, int height) override
    {

        _active_instance = new Instance();
        TileMap map;

        map.Blank(width, height);
        _active_instance->SetTileMap(map);

        _fps_runner.SetRunnable(_active_instance);

        _active_instance->Open();
    }
    enum ClickState
    {
        NO_CLICK,
        SINGLE_PAINT,
        FREE_PAINT,
        BLOCK_PAINTnullptr
    };

    void OnCreateBlankStage() override
    {

    }

    bool OnWindowEvent(sf::Event &e)
    {
        if (ClickOnActiveTileMap(e.mouseButton.x, e.mouseButton.y))
        {
            if (e.type == sf::Event::MouseButtonPressed)
            {
                if (e.mouseButton.button == sf::Mouse::Left)
                {
                    _paint_struct.x1 = e.mouseButton.x;
                    _paint_struct.y1 = e.mouseButton.y;
                    _painting_state = PAINTING;
                }
                else if(e.mouseButton.button == sf::Mouse::Left)
                {
                    _painting_state = DORMANT;
                }
            }
            else if (e.type == sf::Event::MouseButtonReleased)
            {
                if (_painting_state == PAINTING && e.mouseButton.button == sf::Mouse::Left)
                {
                    _paint_struct.x2 = e.mouseButton.x;
                    _paint_struct.y2 = e.mouseButton.y;

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
            return true;
        }
    }

    bool ClickOnActiveTileMap(int x, int y)
    {
        return _active_instance && _active_instance->GetTileMap().TileAt(x, y);
    }

  private:
    FPSRunner _fps_runner;
    DevelopmentOverlay _dev_tools;
    Instance *_active_instance = nullptr;
    PaintStruct _paint_struct;
    PaintingEditState _painting_state = DORMANT;
};

#endif