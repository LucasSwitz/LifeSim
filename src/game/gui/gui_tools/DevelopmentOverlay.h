#ifndef DEVELOPMENTOVERLAY_H
#define DEVELOPMENTOVERLAY_H

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "src/game/gui/gui_tools/Log.h"
#include "src/game/gui/gui_tools/EntityTable.h"
#include "src/game/gui/gui_tools/TileMapEditor.h"
#include "src/world/tile/LuaTileFactory.h"
#include "src/game/gui/TextureCache.h"

class DevelopmentOverlay
{
    public:
        DevelopmentOverlay();
        void Render(sf::RenderWindow& render_window, TextureCache& texture_cache, float seconds_elapsed);
        void Init(sf::RenderWindow& render_window);
        void Shutdown();
        void SetTileMapEditorListener(TileMapEditorListener* listener);
        Log& GetLog();

    private:
        Log _log;
        EntityTable _entity_table;
        TileMapEditor _tile_map_editor;
};
#endif