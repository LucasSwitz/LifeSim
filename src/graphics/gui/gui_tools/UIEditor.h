#ifndef UIEDITOR_H
#define UIEDITOR_H

#include "imgui.h"
#include <unordered_map>
#include "src/graphics/gui/TextureCache.h"
#include "src/graphics/gui/SFMLWindowListener.h"
#include "src/graphics/gui/gui_tools/UIElementEditor.h"


#define DEFAULT_NEW_UI_SIZE 30

class UIEditor : public SFMLWindowListener
{

  public:
      UIElementEditor uie_editor;

    void Init()
    {
        uie_editor.SetUIElementList(UIElementFactory::Instance()->GetAllUIElementBindings());
    }

    void Draw(TextureCache &texture_cache, Brush& brush, bool *p_opened = NULL)
    {
        ImGui::Begin("Instance Editor");
        
            _focused = ImGui::IsRootWindowOrAnyChildHovered();
            if (ImGui::TreeNode("UI Elements##UIEditor"))
            {
                uie_editor.Draw(texture_cache,brush);
                ImGui::TreePop();
            }
        
        ImGui::End();
    }

    bool OnWindowEvent(sf::Event &e) override
    {
        return false;
    }

    bool IsFocused()
    {
        return _focused;
    }

  private:
    int new_instance_dims[2] = {DEFAULT_NEW_UI_SIZE, DEFAULT_NEW_UI_SIZE};
    bool _focused = false;
};

#endif