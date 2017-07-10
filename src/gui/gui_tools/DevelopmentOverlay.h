#ifndef DEVELOPMENTOVERLAY_H
#define DEVELOPMENTOVERLAY_H

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "src/gui/gui_tools/Log.h"
#include "src/gui/gui_tools/EntityTable.h"
#include "src/gui/gui_tools/TileMapEditor.h"
#include "src/world/tile/LuaTileFactory.h"
#include "src/gui/TextureCache.h"

class DevelopmentOverlay
{
    public:
        void Draw(sf::RenderWindow& render_window,  sf::Time &deltaTime);
        void Init(sf::RenderWindow& render_window, TextureCache& texture_cache);
        void Shutdown();
        Log& GetLog();

        static DevelopmentOverlay* Instance()
        {
            static DevelopmentOverlay instance;
            return &instance;
        }
    private:
        DevelopmentOverlay();
        Log _log;
        EntityTable _entity_table;
        TileMapEditor _tile_map_editor;
        TextureCache* _texture_cache;
};
#endif