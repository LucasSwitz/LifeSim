#include "DevelopmentOverlay.h"

DevelopmentOverlay::DevelopmentOverlay()
{

}

void DevelopmentOverlay::Init(PMIDGWindow& window)
{
    ImGui::SFML::Init(window.SFWindow());
    window.AddWindowListener(&tile_map_editor);

    log.Clear();
    tile_map_editor.SetTileList(LuaTileFactory::Instance()->GetAllTileIndentifiers());
}

Log& DevelopmentOverlay::GetLog()
{
    return log;
}

void DevelopmentOverlay::Render(PMIDGWindow&  window, TextureCache& texture_cache, float seconds_elapsed)
{
    sf::Time deltaTime = sf::seconds(seconds_elapsed);
    ImGui::SFML::Update(window.SFWindow(), deltaTime);

// #### DESIGN GUI HERE
    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");

    log.Draw("Log");
    entity_table.Draw("Entities");
    tile_map_editor.Draw("Tile Map Editor", texture_cache);
    ImGui::End();

// #### RENDER GUI HERE
    ImGui::SFML::Render(window.SFWindow());
}

void DevelopmentOverlay::SetTileMapEditorListener(TileMapEditorListener* listener)
{
    tile_map_editor.SetListener(listener);
}

void DevelopmentOverlay::Shutdown()
{
    ImGui::SFML::Shutdown();
}
