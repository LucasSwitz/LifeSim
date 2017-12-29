#ifndef SYSTEMMONITOR_H
#define SYSTEMMONITOR_H

#include "imgui.h"
#include "src/system/SystemFactory.h"
#include "src/system/SystemController.h"

class SystemMonitor
{
  public:
    void Draw(const char *title, SystemController<GameState>& system_controller, bool *opened = NULL)
    {
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
        ImGui::Begin(title, opened);
        _focused = ImGui::IsRootWindowOrAnyChildHovered();

        std::unordered_map<std::string, std::string> available_systems = SystemFactory::Instance()->GetAllSystems();
        auto &active_systems = system_controller.GetExecutionSequenceMutable();
        auto &passive_systems = system_controller.GetPassiveSystemsMutable();

        for (auto it = active_systems.begin(); it != active_systems.end(); it++)
        {
            available_systems.erase((*it)->GetName());
        }

        for (auto it = passive_systems.begin(); it != passive_systems.end(); it++)
        {
            available_systems.erase((*it)->GetName());
        }

        std::vector<std::string> available_systems_vect;

        for (auto it = available_systems.begin(); it != available_systems.end(); it++)
        {
            available_systems_vect.push_back(it->first);
        }

        ImGui::BeginChild("Available Systems", ImVec2(500, 200));

        DrawSystemList(active_systems, system_controller, "Active");
        DrawSystemList(passive_systems, system_controller, "Passive");

        ImGui::EndChild();

        ImGui::BeginChild("Available Systems", ImVec2(500, 0));
        DrawAvailableSystems(available_systems_vect);
        ImGui::EndChild();

        if (ImGui::Button("Enable"))
        {
            if (selected_system != -1)
            {
               system_controller.AddToSystemExecutionSequence(available_systems_vect[selected_system]);
            }
        }
        ImGui::End();
    }

    void DrawAvailableSystems(std::vector<std::string> &systems)
    {
        ImGui::ListBoxVector("##LBVAvialbleSystems", &selected_system, systems);
    }

    void DrawSystemList(SystemController<GameState>::system_list &list, SystemController<GameState>& system_controller, std::string type)
    {
        int i = 0;
        for (auto it = list.begin(); it != list.end();)
        {
            ImGui::Text("%i", i);
            ImGui::SameLine(30);
            std::string name = (*it)->GetName();
            ImGui::Text(name.c_str());
            ImGui::SameLine(200);
            ImGui::Text(type.c_str());
            ImGui::SameLine(300);
            ImGui::Text("%.4f", (*it)->GetLastRuntime());
            ImGui::SameLine(380);
            ImGui::Text("ms");
            ImGui::SameLine(400);
            std::string button_name_up = "+##" + name;
            std::string button_name_down = "-##" + name;
            std::string button_name_kill = "x##" + name;

            if (ImGui::SmallButton(button_name_up.c_str()))
            {
                std::cout << "Moving Up: " << name << std::endl;
                system_controller.MoveUp(name);
            }

            ImGui::SameLine(420);

            if (ImGui::SmallButton(button_name_down.c_str()))
            {
                system_controller.MoveDown(name);
            }
            ImGui::SameLine(440);

            if ((*it)->IsPaused())
            {
                std::string button_name_unpause = ">##" + name;
                if (ImGui::SmallButton(button_name_unpause.c_str()))
                {
                    (*it)->Unpause();
                }
            }
            else
            {
                std::string button_name_pause = "|##" + name;
                if (ImGui::SmallButton(button_name_pause.c_str()))
                {
                    (*it)->Pause();
                }
            }
            ImGui::SameLine(460);
            if (ImGui::SmallButton(button_name_kill.c_str()))
            {
                it = system_controller.RemoveFromSystemExecutionSequence(name);
                continue;
            }

            i++;
            it++;
        }
    }

    bool IsFocused()
    {
        return _focused;
    }

  private:
    bool _focused = false;
    int selected_system = -1;
};
#endif