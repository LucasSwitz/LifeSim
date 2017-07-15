#include "DevelopmentOverlay.h"

DevelopmentOverlay::DevelopmentOverlay()
{

}

void DevelopmentOverlay::Init(PMIDGWindow* window)
{
    ImGui::SFML::Init(window->SFWindow());
    window->AddWindowListener(&instance_editor);
    instance_editor.Init();
    log.Clear();
}

Log& DevelopmentOverlay::GetLog()
{
    return log;
}

void DevelopmentOverlay::Render(PMIDGWindow*  window, TextureCache& texture_cache, float seconds_elapsed)
{
    sf::Time deltaTime = sf::seconds(seconds_elapsed);
    ImGui::SFML::Update(window->SFWindow(), deltaTime);
// #### DESIGN GUI HERE
    DrawMenuBar();
    log.Draw("Log");
    entity_table.Draw("Entities");
    instance_editor.Draw(texture_cache);
// #### RENDER GUI HERE

    ImGui::SFML::Render(window->SFWindow());
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
                    _listener->OnCreateBlankInstance(30,30);
                }                
            }

            if (ImGui::MenuItem("Load Instance", "CTRL+SHIFT+I")) {} 
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Stage"))
        {
            if (ImGui::MenuItem("New Stage", "CTRL+S")) {}
            if (ImGui::MenuItem("Load Stage", "CTRL+SHIFT+S")) {} 
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("World"))
        {
            if (ImGui::MenuItem("New World", "CTRL+W")) {}
            if (ImGui::MenuItem("Load World", "CTRL+SHIFT+W")) {} 
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Entity"))
        {
            if (ImGui::MenuItem("New Entity", "ImGui::EndCTRL+E")) {}
            if (ImGui::MenuItem("Load Entity", "CTRL+SHIFT+E")) {} 
            ImGui::EndMenu();
        }       
        ImGui::EndMainMenuBar(); 
    }
}

bool DevelopmentOverlay::IsFocused()
{
    return log.IsFocused() || entity_table.IsFocused() || instance_editor.IsFocused();
}
void DevelopmentOverlay::Shutdown()
{
    ImGui::SFML::Shutdown();
}

void DevelopmentOverlay::SetListener(DevelopmentOverlayListener* listener)
{
    _listener = listener;
}