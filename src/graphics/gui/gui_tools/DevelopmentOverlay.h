#ifndef DEVELOPMENTOVERLAY_H
#define DEVELOPMENTOVERLAY_H

#include "imgui.h"
#include "imgui-SFML.h"

#include "src/graphics/gui/gui_tools/Log.h"
#include "src/graphics/gui/gui_tools/EntityTable.h"
#include "src/graphics/gui/gui_tools/InstanceEditor.h"
#include "src/world/tile/LuaTileFactory.h"
#include "src/graphics/gui/TextureCache.h"
#include "src/graphics/gui/PMIDGWindow.h"
#include "src/graphics/gui/gui_tools/DevelopmentOverlayListener.h"
#include "src/graphics/gui/gui_tools/SystemMonitor.h"
#include "src/graphics/gui/gui_tools/EditModeControls.h"
#include "src/graphics/gui/gui_tools/MainMenu.h"
#include "src/graphics/gui/gui_tools/StageEditor.h"
#include "src/game/GameState.h"

class DevelopmentOverlay : public MainMenuListener, public EditModeControlsListener
{
    public:
        DevelopmentOverlay();
        void Render(PMIDGWindow* render_window, GameState* game_state, TextureCache& texture_cache, float seconds_elapsed, Brush& brush);
        void Init(PMIDGWindow* render_window);
        void Shutdown();
        Log& GetLog();
        void SetListener(DevelopmentOverlayListener* listener);
        bool IsFocused();

        // Inhertited from MainMenuListener
        void NewInstancePressed(std::string& name);
        void LoadInstancePressed(std::string& file_name);
        void SaveInstancePressed(std::string& file_name);
        void LoadStagePressed(std::string& file_name);
        void SaveStagePressed(std::string& file_name);
        void NewStagePressed();

        //Inherited from EditModeControlListener
        void OnLaunchStage();
        void OnLaunchInstance();

        Log log;
        EntityTable entity_table;
        InstanceEditor instance_editor;
        SystemMonitor system_monitor;
        EditModeControls edit_mode_controls;
        MainMenu main_menu;
        StageEditor stage_editor;

    private:
        void DrawMenuBar();
        DevelopmentOverlayListener* _listener = nullptr;
        bool _focused = false;

        InputDialog _save_dialog;
};
#endif