#ifndef UIELEMENTEDITOR_H
#define UIELEMENTEDITOR_H

#include "src/graphics/gui/TextureCache.h"
#include "src/graphics/gui/brush/Brush.h"
#include "src/graphics/gui/gui_tools/ComponentUserEditor.h"
#include "src/graphics/gui/imgui_extension/ImGuiExtension.h"
#include "src/ui/UIElementFactory.h"
#include "src/graphics/gui/brush/PaintUIElementBrushState.h"
#include "src/graphics/gui/brush/PaintContainerBrushState.h"
class UIElementEditor
{
  public:
    template <typename IterableContainer>
    void SetEntityList(const IterableContainer &scripts)
    {
        ui_elements.clear();

        for (auto script : scripts)
        {
            ui_elements.push_back(script);
        }
    }

    template <typename T>
    void SetUIElementList(const T &scripts)
    {
        ui_elements.clear();

        for (auto it = scripts.begin(); it != scripts.end(); it++)
        {
            ui_elements.push_back(it->first);
        }
    }

    void Draw(TextureCache &texture_cache, Brush &brush)
    {
        ImGui::ListBoxVector("##UIElementEditorLBV", &selected_element, ui_elements);

        if (selected_element != -1)
        {
            if (!selected_uie_prototype || selected_uie_prototype->Name().compare(ui_elements.at(selected_element)) != 0)
            {
                delete selected_uie_prototype;
                selected_uie_prototype = UIElementFactory::Instance()
                                             ->GetUIElement(ui_elements.at(selected_element));
                
                brush.SetState(std::make_shared<PaintUIElementBrushState>(selected_uie_prototype));
            }

            if (selected_uie_prototype && selected_uie_prototype->HasComponent("Graphics"))
            {
                std::string texture_path = selected_uie_prototype->GetComponentValueString("Graphics", "sprite");
                ptr<sf::Texture> texture = texture_cache.GetTexture(texture_path);
                ImGui::Image(*texture);
                ImGui::SameLine();
            }

            _component_editor.Draw(*selected_uie_prototype);
        }
    }

  private:
    ComponentUserEditor _component_editor;
    std::vector<std::string> ui_elements;
    UIElement *selected_uie_prototype = nullptr;
    int selected_element = -1;
};
#endif