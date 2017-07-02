#include "imgui.h"
#include "src/game_objects/EntityManager.h"
#include "src/game_objects/Entity.h"

struct EntityTable
{
    void Draw(const char* title, bool* opened = NULL)
    {
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
        ImGui::Begin(title, opened);

        std::map<int, Entity*>& map = EntityManager::Instance()->GetAllEntities(); 

        for(auto it = map.begin(); it != map.end(); it++)
        {
          ImGui::Text("%i",it->first); ImGui::SameLine(50); ImGui::Text((it->second->GetPrototypeName()).c_str());
        }

        ImGui::End();
    }
};