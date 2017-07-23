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

void DevelopmentOverlay::Render(PMIDGWindow*  window, TextureCache& texture_cache, float seconds_elapsed, Brush& brush)
{
    sf::Time deltaTime = sf::seconds(seconds_elapsed);
    ImGui::SFML::Update(window->SFWindow(), deltaTime);
// #### DESIGN GUI HERE_selcected_file
    DrawMenuBar();
    log.Draw("Log");
    entity_table.Draw("Entities");
    instance_editor.Draw(texture_cache, brush);
    system_monitor.Draw("System Monitor");
    edit_mode_controls.Draw("Edit Mode Controls", *window);
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

            if (ImGui::BeginMenu("Load Instance", "CTRL+SHIFT+I")) 
            {
                FolderContents instance_files("/home/pabu/Desktop/LifeSim/src/graphics/gui/gui_tools");
                ImGui::BeginChild("Instance Selection",ImVec2(300,200),true,ImGuiWindowFlags_NoScrollbar);
                instance_files.Draw();
                ImGui::EndChild();
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Save Instance", "CTRL+SHIFT+I")) 
            {
                ImGui::BeginChild("Select Instance");
                ImGui::Text("Test");
                ImGui::EndChild();
            } 
            if (ImGui::MenuItem("Save As Instance....", "CTRL+SHIFT+I")) 
            {
                ImGui::BeginChild("Select Instance");
                ImGui::Text("Test");
                ImGui::EndChild();
            } 
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
    return log.IsFocused() || entity_table.IsFocused() || 
    instance_editor.IsFocused() || system_monitor.IsFocused()
    || edit_mode_controls.IsFocused();
}
void DevelopmentOverlay::Shutdown()
{
    ImGui::SFML::Shutdown();
}

void DevelopmentOverlay::SetListener(DevelopmentOverlayListener* listener)
{
    _listener = listener;
}