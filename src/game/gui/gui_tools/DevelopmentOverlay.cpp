#include "DevelopmentOverlay.h"

DevelopmentOverlay::DevelopmentOverlay()
{

}

void DevelopmentOverlay::Init(sf::RenderWindow& window)
{
    ImGui::SFML::Init(window);
    
    _log.Clear();
    _tile_map_editor.SetTileList(LuaTileFactory::Instance()->GetAllTileIndentifiers());
}

Log& DevelopmentOverlay::GetLog()
{
    return _log;
}

void DevelopmentOverlay::Render(sf::RenderWindow& window, TextureCache& _texture_cache, float seconds_elapsed)
{
    sf::Time deltaTime = sf::seconds(seconds_elapsed);
    ImGui::SFML::Update(window, deltaTime);

// #### DESIGN GUI HERE
    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");

    _log.Draw("Log");
    _entity_table.Draw("Entities");
    _tile_map_editor.Draw("Tile Map Editor", _texture_cache);
    ImGui::End();

// #### RENDER GUI HERE
    ImGui::SFML::Render(window);
}

void DevelopmentOverlay::SetTileMapEditorListener(TileMapEditorListener* listener)
{
    _tile_map_editor.SetListener(listener);
}

void DevelopmentOverlay::Shutdown()
{
    ImGui::SFML::Shutdown();
}
