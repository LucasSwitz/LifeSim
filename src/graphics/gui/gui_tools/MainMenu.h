#ifndef MAINMENU_H
#define MAINMENU_H

#include "imgui.h"
#include "src/graphics/gui/gui_tools/FolderContents.h"
#include "src/graphics/gui/gui_tools/InputDialog.h"
#include "src/graphics/gui/gui_tools/MainMenuListener.h"
#include "src/game/GameState.h"

class MainMenu
{
  public:
    void Draw(ptr<GameState> game_state)
    {
        if (ImGui::BeginMainMenuBar())
        {
            _focused = ImGui::IsRootWindowOrAnyChildHovered();

            if (ImGui::BeginMenu("File"))
            {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Instance", game_state->GetStage().get()))
            {
                if (ImGui::BeginMenu("New Instance", "CTRL+I"))
                {
                    ImGui::BeginChild("Instance Name##Menu", ImVec2(300, 200), true, ImGuiWindowFlags_NoScrollbar);
                    std::string instance_name = _new_instance_dialog.Draw();
                    ImGui::EndChild();
                    ImGui::EndMenu();

                    if (!instance_name.empty())
                    {
                        if (_listener)
                        {
                            _listener->NewInstancePressed(instance_name);
                        }
                    }
                }
            }
            if (ImGui::BeginMenu("Stage"))
            {
                if (ImGui::MenuItem("New Stage", "CTRL+S"))
                {
                    if (_listener)
                    {
                        _listener->NewStagePressed();
                    }
                }
                if (ImGui::BeginMenu("Load Stage", "CTRL+SHIFT+S"))
                {
                    _focused = true;
                    ImGui::BeginChild("Stage Selection##Menu", ImVec2(300, 200), true, ImGuiWindowFlags_NoScrollbar);
                    FolderContents stage_files(Globals::RESOURCE_ROOT + "/world/stages");
                    std::string file_name = stage_files.Draw();
                    if (!file_name.empty())
                    {
                        if (_listener)
                        {
                            _listener->LoadStagePressed(file_name);
                        }
                    }
                    ImGui::EndChild();
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Save as Stage..."))
                {
                    ImGui::BeginChild("Save Stage##Menu", ImVec2(250, 50), true, ImGuiWindowFlags_NoScrollbar);
                    std::string file_name = _save_dialog.Draw();

                    if (!file_name.empty())
                    {
                        if (_listener)
                        {
                            _listener->SaveStagePressed(file_name);
                        }
                    }

                    ImGui::EndChild();
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("World"))
            {
                if (ImGui::MenuItem("New World", "CTRL+W"))
                {
                }
                if (ImGui::MenuItem("Load World", "CTRL+SHIFT+W"))
                {
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Entity"))
            {
                if (ImGui::MenuItem("New Entity", "ImGui::EndCTRL+E"))
                {
                }
                if (ImGui::MenuItem("Load Entity", "CTRL+SHIFT+E"))
                {
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("UI"))
            {
                if (ImGui::MenuItem("New UI", "CTRL+W"))
                {
                    
                }
                if (ImGui::MenuItem("Attach UI", "CTRL+SHIFT+W"))
                {

                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    bool IsFocused()
    {
        return _focused || _save_dialog.IsFocused();
    }

    void SetListener(MainMenuListener *listener)
    {
        _listener = listener;
    }

  private:
    MainMenuListener *_listener;
    InputDialog _save_dialog;
    InputDialog _new_instance_dialog;
    bool _focused = false;
};
#endif