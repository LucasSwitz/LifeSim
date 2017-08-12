#ifndef EDITMODECONTROLS_H
#define EDITMODECONTROLS_H

#include "imgui.h"
#include "src/component/ComponentUserBase.h"
#include "src/graphics/gui/PMIDGWindow.h"

class EditModeControlsListener
{
  public:
    virtual void OnLaunchGameRunner() {}
    virtual void OnStopGameRunner() {}
};

class EditModeControls
{
  public:
    void Draw(const char *title, PMIDGWindow &window, bool *opened = NULL)
    {
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
        ImGui::Begin(title, opened);
        _focused = ImGui::IsRootWindowOrAnyChildHovered();

        ImGui::Checkbox("Show Hitboxes", &_show_collision_boxes);

        if (_show_collision_boxes)
        {
            std::list<ComponentUser *> *users = ComponentUserBase::Instance()->GetAllUsersWithComponent("Collision");

            if (users)
            {
                for (ComponentUser *user : *users)
                {
                    int width = user->GetComponentValueFloat("Collision", "width");
                    int height = user->GetComponentValueFloat("Collision", "height");
                    int x = user->GetComponentValueFloat("Position", "x");
                    int y = user->GetComponentValueFloat("Position", "y");

                    sf::RectangleShape rect(sf::Vector2f(width, height));
                    sf::CircleShape circ(2);
                    circ.setFillColor(sf::Color::Green);
                    circ.setPosition(x, y);
                    window.DrawNow(circ);

                    rect.setOutlineColor(sf::Color::Red);
                    rect.setOutlineThickness(2);
                    rect.setFillColor(sf::Color::Transparent);
                    rect.setPosition(x - width / 2, y - height / 2);
                    window.DrawNow(rect);
                }
            }
        }

        if (!_play_button_down)
        {
            if (ImGui::Button("Play##NotStarted"))
            {
                if (_listener)
                    _listener->OnLaunchGameRunner();
                _play_button_down = true;
            }
        }
        else
        {
            if (!_pause_button_down)
            {
                if (ImGui::Button("Pause"))
                {
                    _pause_button_down = true;
                }
            }
            else
            {
                if (ImGui::Button("Play##Started"))
                    _pause_button_down = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Stop"))
            {
                if (_listener)
                    _listener->OnStopGameRunner();
                _play_button_down = false;
            }
        }
        ImGui::End();
    }

    bool IsFocused()
    {
        return _focused;
    }

    void SetListener(EditModeControlsListener *listener)
    {
        _listener = listener;
    }

  private:
    bool _focused = false;
    bool _show_collision_boxes = false;
    bool _play_button_down = false;
    bool _pause_button_down = false;
    EditModeControlsListener *_listener = nullptr;
};
#endif
