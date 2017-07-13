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
    bool opened;
// #### DESIGN GUI HERE
    DrawMenuBar();
    log.Draw("Log");
    entity_table.Draw("Entities");
    //ImVec2 size(500,600);
    tile_map_editor.Draw(texture_cache);

// #### RENDER GUI HERE
    ImGui::SFML::Render(window.SFWindow());
}

void DevelopmentOverlay::DrawMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Instance"))
        {
            if (ImGui::MenuItem("New Instance", "CTRL+I")) 
            {
                if(_listener)
                {
                    _listener.
                }
            }

            if (ImGui::MenuItem("Load Instance", "CTRL+SHIFT+I")) {}  // Disabled item
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Stage"))
        {
            if (ImGui::MenuItem("New Stage", "CTRL+S")) {}
            if (ImGui::MenuItem("Load Stage", "CTRL+SHIFT+S")) {}  // Disabled item
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("World"))
        {
            if (ImGui::MenuItem("New World", "CTRL+W")) {}
            if (ImGui::MenuItem("Load World", "CTRL+SHIFT+W")) {}  // Disabled item
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Entity"))
        {
            if (ImGui::MenuItem("New Entity", "CTRL+E")) {}
            if (ImGui::MenuItem("Load Entity", "CTRL+SHIFT+E")) {}  // Disabled item
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void DevelopmentOverlay::Shutdown()
{
    ImGui::SFML::Shutdown();
}


void DevelopmentOverlay::SetListener(DevelopmentOverlayListener* listener)
{
    _listener = listener;
}