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

  public:
    void Draw(TextureCache &texture_cache, ComponentUser &user)
    {
        if ( ImGui::BeginChild("Components"))
        {
            DrawComponentControllers(user);

            ImGui::EndChild();
        }
    }

    void DrawComponentControllers(ComponentUser &user)
    {
        std::unordered_map<std::string, Component*> components = user.GetAllComponents();

        for (auto it = components.begin(); it != components.end(); it++)
        {
            Component *current_component = it->second;
            std::string component_name = it->first;

            if (ImGui::TreeNode(component_name.c_str()))
            {
               
               std::unordered_map<std::string, Component::ComponentValue<std::string>> string_values = current_component->GetAllStringValues();
               std::unordered_map<std::string, Component::ComponentValue<float>> float_values = current_component->GetAllFloatValues();
               std::unordered_map<std::string, Component::ComponentValue<bool>> bool_values = current_component->GetAllBoolValues();

                for (auto it = string_values.begin(); it != string_values.end(); it++)
                {
                    std::string current_key = it->first;
                    std::string current_value = it->second.GetValue();

                    if(!HasStringInput(current_key))
                        AddStringInput(current_key, current_value);
                    
                    char* input = _string_inputs.at(current_key);

                    if(ImGui::Button("Update"))
                    {
                        std::string new_string_value(input);
                        
                    }
                    ImGui::SameLine();
                    ImGui::InputText(current_key.c_str(), input, 512);
                }

                for (auto it = float_values.begin(); it != float_values.end(); it++)
                {
                    std::string current_key = it->first;
                    int current_value = it->second.GetValue();

                    ImGui::InputInt(current_key.c_str(),&current_value);
                }   

                for (auto it = bool_values.begin(); it != bool_values.end(); it++)
                {

                }

                ImGui::TreePop();
            }
        }
    }

    bool OnWindowEvent(sf::Event& e)
    {
        return false;
    }

    bool HasStringInput(std::string name)
    {
        return _string_inputs.find(name) != _string_inputs.end();
    }

    void AddStringInput(std::string name, std::string value)
    {
        char* input = new char[512];
        value.copy(input, value.length());
        _string_inputs.insert(std::make_pair(name, input));
    }

    private:
        std::unordered_map<std::string, char*> _string_inputs;

    void Close()
    {
        for(auto it = _string_inputs.begin(); it != _string_inputs.end(); it++)
        {
            delete it->second;
        }

        _string_inputs.clear();
    }
};

#endif