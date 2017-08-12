#include "DevelopmentOverlay.h"

DevelopmentOverlay::DevelopmentOverlay()
{
}

void DevelopmentOverlay::Init(PMIDGWindow *window)
{
    ImGui::SFML::Init(window->SFWindow());
    window->AddWindowListener(&instance_editor);
    instance_editor.Init();
    log.Clear();
    main_menu.SetListener(this);
    edit_mode_controls.SetListener(this);
}

Log &DevelopmentOverlay::GetLog()
{
    return log;
}

void DevelopmentOverlay::Render(PMIDGWindow *window, TextureCache &texture_cache, float seconds_elapsed, Brush &brush)
{
    sf::Time deltaTime = sf::seconds(seconds_elapsed);
    ImGui::SFML::Update(window->SFWindow(), deltaTime);

    brush.DrawExtras();
    
    if (!IsFocused())
        brush.PaintWindow(*window);
    // #### DESIGN GUI HERE_selcected_file
    main_menu.Draw();
    log.Draw("Log");
    entity_table.Draw("Entities");
    instance_editor.Draw(texture_cache, brush);
    system_monitor.Draw("System Monitor");
    edit_mode_controls.Draw("Edit Mode Controls", *window);
    // #### RENDER GUI HERE

    ImGui::SFML::Render(window->SFWindow());
}

void DevelopmentOverlay::LoadInstancePressed(std::string &file_name)
{
    if (_listener)
    {
        _listener->OnLoadGameStateFile(file_name);
    }
}

void DevelopmentOverlay::SaveInstancePressed(std::string &file_name)
{
    if (_listener)
    {
        _listener->OnSaveGameStateFile(file_name);
    }
}

void DevelopmentOverlay::NewInstancePressed()
{
    if (_listener)
    {
        _listener->OnCreateBlankInstance(30, 30);
    }
}

bool DevelopmentOverlay::IsFocused()
{
    return log.IsFocused() || entity_table.IsFocused() ||
           instance_editor.IsFocused() || system_monitor.IsFocused() || edit_mode_controls.IsFocused() || main_menu.IsFocused();
}
void DevelopmentOverlay::Shutdown()
{
    ImGui::SFML::Shutdown();
}

void DevelopmentOverlay::SetListener(DevelopmentOverlayListener *listener)
{
    _listener = listener;
}

void DevelopmentOverlay::OnLaunchGameRunner()
{
    if(_listener)
        _listener->OnLaunchGameRunner();
}
void DevelopmentOverlay::OnStopGameRunner()
{
    if(_listener)
        _listener->OnStopGameRunner();
}