#ifndef PROGRAMMODEEDITOR_H
#define PROGRAMMODEEDITOR_H

#include "src/game/mode/ProgramMode.h"
#include "src/game/gui/gui_tools/DevelopmentOverlay.h"
#include "src/system/SystemController.h"
#include "src/game/FPSRunner.h"


class ProgramModeEditor : public ProgramMode, public TileMapEditorListener
{
    public:
    ProgramModeEditor()
    {
        
    }

    void Init(PMIDGWindow& window)
    {
        SystemController::Instance()->AddToSystemExecutionSequence("DrawGraphicsSystem");
        LuaTileFactory::Instance()->PopulateFactory();

        _dev_tools.Init(window.SFWindow());
        _dev_tools.SetTileMapEditorListener(this);
    }

    void Update(float seconds_elapsed) override
    {
        _fps_runner.Update(seconds_elapsed);
    }

    void Render(PMIDGWindow& window, float seconds_elapsed) override
    {
        //chance to draw Dev Tools
        _dev_tools.Render(window.SFWindow(),window.GetTextureCache(), seconds_elapsed);
    }

    void OnSFEvent(sf::Event& event)
    {
        _fps_runner.OnSFEvent(event);
    }

    void Exit() override
    {
        _dev_tools.Shutdown();
    }

    void OnCreateBlankInstance(int width, int height) override
    {

        Instance* instance = new Instance();
        TileMap map;

        map.Blank(width,height);
        instance->SetTileMap(map);
        _fps_runner.SetRunnable(instance);

        instance->Open();
    }

    void OnCreateBlankStage() override
    {

    }   

    private:
        FPSRunner _fps_runner;
        DevelopmentOverlay _dev_tools;
};
#endif