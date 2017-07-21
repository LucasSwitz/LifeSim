#ifndef InstanceEditor_H
#define InstanceEditor_H

#include "imgui.h"
#include <stdarg.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "src/graphics/gui/imgui_extension/ImGuiExtension.h"
#include "src/graphics/gui/TextureCache.h"
#include "src/world/tile/TileMap.h"
#include "src/graphics/gui/SFMLWindowListener.h"
#include "src/graphics/gui/gui_tools/ComponentUserEditor.h"
#include "src/graphics/gui/gui_tools/TileMapEditor.h"
#include "src/graphics/gui/gui_tools/EntityEditor.h"

#define DEFAULT_NEW_INSTANCE_SIZE 30

class InstanceEditor : public SFMLWindowListener
{

  public:
      TileMapEditor tile_map_editor;
      EntityEditor entity_editor;

    void Init()
    {
        tile_map_editor.SetTileList(LuaTileFactory::Instance()->GetAllTileIndentifiers());
        entity_editor.SetEntityList(LuaEntityFactory::Instance()->GetAllEntityIdentifiers());
    }
    void Draw(TextureCache &texture_cache, Brush& brush, bool *p_opened = NULL)
    {
        ImGui::Begin("Instance Editor");
        
            _focused = ImGui::IsRootWindowOrAnyChildHovered();
            if (ImGui::TreeNode("Tile Map"))
            {
                tile_map_editor.Draw(texture_cache,brush);
                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Entites"))
            {
                entity_editor.Draw(texture_cache,brush);
                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Events"))
            {
                ImGui::TreePop();
            }

            ImGui::InputInt2("##Resize Instance", new_instance_dims);
            ImGui::SameLine();
            if (ImGui::Button("Resize Instance"))
            {
                //this thing needs a reference of the instance
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
    int new_instance_dims[2] = {DEFAULT_NEW_INSTANCE_SIZE, DEFAULT_NEW_INSTANCE_SIZE};
    bool _focused = false;
};

#endif