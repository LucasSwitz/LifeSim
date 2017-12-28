#ifndef COMPONENTUSEREDITOR
#define COMPONENTUSEREDITOR

#include "imgui.h"
#include <stdarg.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "src/world/tile/LuaTileFactory.h"
#include "src/graphics/gui/imgui_extension/ImGuiExtension.h"
#include "src/graphics/gui/TextureCache.h"
#include "src/graphics/gui/SFMLWindowListener.h"
#include "src/component/ComponentUser.h"

class ComponentUserEditor : public SFMLWindowListener
{

    static int cue_count;

  public:
    ComponentUserEditor()
    {
        _label = "##ComponentUserController" + std::to_string(cue_count);
        cue_count++;
    }

    void Draw(ComponentUser &user)
    {
        std::string label = "Components" + _label;
        DrawComponentControllers(user);
    }

    void DrawComponentControllers(ComponentUser &user)
    {
        auto components = user.GetAllComponents();

        for (auto it = components.begin(); it != components.end(); it++)
        {
            ptr<Component> current_component = it->second;
            std::string component_name = it->first;

            std::string label = component_name.c_str() + _label;

            if (ImGui::TreeNode(label.c_str()))
            {
                auto &string_values = current_component->GetAllStringValues();
                auto &float_values = current_component->GetAllFloatValues();
                auto &bool_values = current_component->GetAllBoolValues();

                for (auto it = string_values.begin(); it != string_values.end(); it++)
                {
                    std::string current_key = it->first;
                    std::string current_value = it->second.GetValue();

                    if (!HasStringInput(current_key))
                        AddStringInput(current_key, current_value);

                    char *input = _string_inputs.at(current_key);

                    std::string label = "Update" + _label;
                    if (ImGui::Button(label.c_str()))
                    {
                        std::string new_string_value(input);
                    }
                    ImGui::SameLine();

                    label = current_key + _label;
                    ImGui::InputText(label.c_str(), input, 512);
                }

                for (auto it = float_values.begin(); it != float_values.end(); it++)
                {
                    std::string current_key = it->first;

                    std::string label = current_key + _label;
                    ImGui::InputFloat(label.c_str(), it->second.GetValuePtr(), .1f, 1.0f);
                }

                for (auto it = bool_values.begin(); it != bool_values.end(); it++)
                {
                }
                ImGui::TreePop();
            }
        }
    }

    bool OnWindowEvent(sf::Event &e)
    {
        return false;
    }

    bool HasStringInput(std::string name)
    {
        return _string_inputs.find(name) != _string_inputs.end();
    }

    void AddStringInput(std::string name, std::string value)
    {
        char *input = new char[512];
        value.copy(input, value.length());
        _string_inputs.insert(std::make_pair(name, input));
    }

  private:
    std::unordered_map<std::string, char *> _string_inputs;
    std::string _label;

    void Close()
    {
        for (auto it = _string_inputs.begin(); it != _string_inputs.end(); it++)
        {
            delete it->second;
        }

        _string_inputs.clear();
    }
};

#endif