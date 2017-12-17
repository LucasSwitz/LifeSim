#include "DevelopmentOverlay.h"

DevelopmentOverlay::DevelopmentOverlay()
{
    
}

void DevelopmentOverlay::Init(ptr<PMIDGWindow> window)
{
    ImGui::SFML::Init(window->SFWindow());
    window->AddWindowListener(ptr<SFMLWindowListener> (&instance_editor));
    instance_editor.Init();
    log.Clear();
    main_menu.SetListener(this);
    edit_mode_controls.SetListener(this);
}

Log &DevelopmentOverlay::GetLog()
{
    return log;
}

void DevelopmentOverlay::Render(ptr<PMIDGWindow> window, ptr<GameState> game_state,
                                TextureCache &texture_cache, float seconds_elapsed, Brush &brush)
{

    sf::Time deltaTime = sf::seconds(seconds_elapsed);
    ImGui::SFML::Update(window->SFWindow(), deltaTime);

    brush.DrawExtras();

    if (!IsFocused())
        brush.PaintWindow(*window);
    // #### DESIGN GUI HERE_selcected_file
    main_menu.Draw(game_state);
    log.Draw("Log");
    system_monitor.Draw("System Monitor", game_state->GetSystemController());
    edit_mode_controls.Draw("Edit Mode Controls", *window,*game_state);

    if(game_state->GetStage())
    {
        stage_editor.Draw(game_state->GetStage());
        entity_table.Draw("Entities", *(game_state->GetEntityManager())); 
        instance_editor.Draw(texture_cache, brush);        
    }
    // #### RENDER GUI HERE

    ImGui::SFML::Render(window->SFWindow());
}

void DevelopmentOverlay::NewInstancePressed(std::string& instance_name)
{
    if (_listener)
    {
        _listener->OnCreateBlankInstance(instance_name, 30, 30);
    }
}

void DevelopmentOverlay::NewStagePressed()
{
    if (_listener)
    {
        _listener->OnCreateBlankStage();
    }
}

void DevelopmentOverlay::LoadStagePressed(std::string &file_name)
{
    if (_listener)
    {
        _listener->OnLoadStageFile(file_name);
    }
}

void DevelopmentOverlay::SaveStagePressed(std::string &file_name)
{
    if (_listener)
    {
        _listener->OnSaveStageFile(file_name);
    }
}

bool DevelopmentOverlay::IsFocused()
{
    return log.IsFocused() || entity_table.IsFocused() ||
           instance_editor.IsFocused() || system_monitor.IsFocused() || edit_mode_controls.IsFocused() ||
           main_menu.IsFocused() || stage_editor.IsFocused();
}
void DevelopmentOverlay::Shutdown()
{
    ImGui::SFML::Shutdown();
}

void DevelopmentOverlay::SetListener(ptr<DevelopmentOverlayListener> listener)
{
    _listener = listener;
}

void DevelopmentOverlay::OnLaunchStage()
{
    if (_listener)
        _listener->OnLaunchStage();
}
void DevelopmentOverlay::OnLaunchInstance()
{
    if (_listener)
        _listener->OnLaunchInstance();
}