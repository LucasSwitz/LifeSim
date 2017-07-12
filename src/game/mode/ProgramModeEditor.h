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
    ProgramModeEditor()
    {
    }

    void Init(PMIDGWindow &window)
    {
        SystemController::Instance()->AddToSystemExecutionSequence("DrawGraphicsSystem");
        LuaTileFactory::Instance()->PopulateFactory();

        _dev_tools.Init(window);
        _dev_tools.SetTileMapEditorListener(this);
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

    void OnCreateBlankStage() override
    {

    }

    bool OnWindowEvent(sf::Event &e)
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                Tile* clicked_tile = nullptr;
                if (clicked_tile = ClickOnActiveTileMap(e.mouseButton.x, e.mouseButton.y))
                {
                    std::string new_texture_path = _dev_tools.tile_map_editor.GetSelectedTexturePath();
                    if(!new_texture_path.empty())
                    {
                        clicked_tile->SetComponentValueString("Graphics","sprite",new_texture_path);
                    }
                }
            }
        }
    }

    Tile* ClickOnActiveTileMap(int x, int y)
    {
        if(_active_instance)
        {
            return _active_instance->GetTileMap().TileAt(x,y);
        }
        return nullptr;   
    }

  private:
    FPSRunner _fps_runner;
    DevelopmentOverlay _dev_tools;
    Instance* _active_instance = nullptr;
};
#endif