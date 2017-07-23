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
#include "src/graphics/gui/gui_tools/FolderContents.h"
#include "src/graphics/gui/gui_tools/SaveDialog.h"

class DevelopmentOverlay
{
    public:
        DevelopmentOverlay();
        void Render(PMIDGWindow* render_window, TextureCache& texture_cache, float seconds_elapsed, Brush& brush);
        void Init(PMIDGWindow* render_window);
        void Shutdown();
        Log& GetLog();
        void SetListener(DevelopmentOverlayListener* listener);
        bool IsFocused();

        Log log;
        EntityTable entity_table;
        InstanceEditor instance_editor;
        SystemMonitor system_monitor;
        EditModeControls edit_mode_controls;

    private:
        void DrawMenuBar();
        DevelopmentOverlayListener* _listener = nullptr;
        bool _focused = false;

        SaveDialog _save_dialog;
};
#endif