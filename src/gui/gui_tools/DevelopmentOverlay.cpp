#include "DevelopmentOverlay.h"

DevelopmentOverlay::DevelopmentOverlay()
{

}

void DevelopmentOverlay::Init(sf::RenderWindow& window, TextureCache& texture_cache)
{
    ImGui::SFML::Init(window);
    _log.Clear();
    _tile_map_editor.SetTileList(LuaTileFactory::Instance()->GetAllTileIndentifiers());
    _texture_cache = &texture_cache;
}

Log& DevelopmentOverlay::GetLog()
{
    return _log;
}

void DevelopmentOverlay::Draw(sf::RenderWindow& window, sf::Time& deltaTime)
{
    sf::Event event;
    ImGui::SFML::Update(window, deltaTime);

// #### DESIGN GUI HERE
    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");

    _log.Draw("Log");
    _entity_table.Draw("Entities");
    _tile_map_editor.Draw("Tile Map Editor", *_texture_cache);
    ImGui::End();

// #### RENDER GUI HERE
    ImGui::SFML::Render(window);
}

void DevelopmentOverlay::Shutdown()
{
    ImGui::SFML::Shutdown();
}
