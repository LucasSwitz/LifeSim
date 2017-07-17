#ifndef EDITMODECONTROLS_H
#define EDITMODECONTROLS_H

#include "imgui.h"
#include "src/component/ComponentUserBase.h"
#include "src/game/gui/PMIDGWindow.h"

struct EditModeControls
{
    void Draw(const char* title, PMIDGWindow& window, bool* opened = NULL)
    {
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
        ImGui::Begin(title, opened);
        _focused = ImGui::IsRootWindowOrAnyChildHovered();

        ImGui::Checkbox("Show Hitboxes", &_show_collision_boxes);



        if(_show_collision_boxes)
        {
            std::list<ComponentUser*>* users =  ComponentUserBase::Instance()->GetAllUsersWithComponent("Collision");
            for(ComponentUser* user : *users)
            {
                int width = user->GetComponentValueFloat("Collision","width");
                int height = user->GetComponentValueFloat("Collision","height");
                int x = user->GetComponentValueFloat("Position","x");
                int y = user->GetComponentValueFloat("Position","y");

                sf::RectangleShape rect(sf::Vector2f(width, height));
                rect.setOutlineColor(sf::Color::Red);
                rect.setOutlineThickness(2);
                rect.setFillColor(sf::Color::Transparent);
                rect.setPosition(x-width/2.0,y-height/2.0);
                window.DrawNow(rect);
            }
        }

        ImGui::End();
    }
    
    bool IsFocused()
    {
        return _focused;
    }

    private:
        bool _focused = false;
        bool _show_collision_boxes = false;    
};
#endif
