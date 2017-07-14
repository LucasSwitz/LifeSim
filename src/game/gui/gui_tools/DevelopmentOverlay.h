#ifndef DEVELOPMENTOVERLAY_H
#define DEVELOPMENTOVERLAY_H

#include "imgui.h"
#include "imgui-SFML.h"

#include "src/game/gui/gui_tools/Log.h"
#include "src/game/gui/gui_tools/EntityTable.h"
#include "src/game/gui/gui_tools/InstanceEditor.h"
#include "src/world/tile/LuaTileFactory.h"
#include "src/game/gui/TextureCache.h"
#include "src/game/gui/PMIDGWindow.h"
#include "src/game/gui/gui_tools/DevelopmentOverlayListener.h"

class DevelopmentOverlay
{
    public:
        DevelopmentOverlay();
        void Render(PMIDGWindow* render_window, TextureCache& texture_cache, float seconds_elapsed);
        void Init(PMIDGWindow* render_window);
        void Shutdown();
        Log& GetLog();
        void SetListener(DevelopmentOverlayListener* listener);

        Log log;
        EntityTable entity_table;
        InstanceEditor tile_map_editor;

    private:
        void DrawMenuBar();
        DevelopmentOverlayListener* _listener = nullptr;
};
#endif