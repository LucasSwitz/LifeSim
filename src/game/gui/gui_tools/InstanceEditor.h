#ifndef InstanceEditor_H
#define InstanceEditor_H

#include "imgui.h"
#include <stdarg.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "src/world/tile/LuaTileFactory.h"
#include "src/game/gui/imgui_extension/ImGuiExtension.h"
#include "src/world/tile/Tile.h"
#include "src/game/gui/TextureCache.h"
#include "src/world/tile/TileMap.h"
#include "src/game/gui/SFMLWindowListener.h"

#define DEFAULT_NEW_INSTANCE_SIZE  30

class InstanceEditor : public SFMLWindowListener
{

  public:
    template <typename IterableContainer>
    void SetTileList(const IterableContainer &scripts)
    {
        tile_scripts.clear();

        for (auto script : scripts)
        {
            tile_scripts.push_back(script);
        }
    }

    void SetTileList(const std::unordered_map<int, std::string> &scripts)
    {
        tile_scripts.clear();

        for (auto it = scripts.begin(); it != scripts.end(); it++)
        {
            tile_scripts.push_back(it->second);
        }
    }

    void Draw(TextureCache &texture_cache, bool *p_opened = NULL)
    {
        if (ImGui::Begin("Instance Editor"))
        {
            if (ImGui::TreeNode("Tile Map"))
            {
                ImGui::ListBoxVector("", &selected_tile, tile_scripts);

                if (selected_tile != -1)
                {
                    selected_tile_prototype = LuaTileFactory::Instance()->GetTile(tile_scripts.at(selected_tile));
                    std::string texture_path = selected_tile_prototype->GetComponentValueString("Graphics", "sprite");

                    ImGui::LabelText("Path: ", texture_path.c_str());

                    ImGui::Image(*texture_cache.GetTexture(texture_path));
                    //find some way to edit other components
                }    
                
                ImGui::InputInt2("##Resize Instance", new_instance_dims);
                ImGui::SameLine();
                if(ImGui::Button("Resize Instance"))
                {
                    //this thing needs a reference of the instance
                }

                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Entites"))
            {
                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Events"))
            {
                ImGui::TreePop();
            }

            ImGui::End();
        }
    }

    std::string GetSelectedTexturePath()
    {
        if (selected_tile_prototype)
            return selected_tile_prototype->GetComponentValueString("Graphics", "sprite");
        else
            return "";
    }

    bool OnWindowEvent(sf::Event &e) override
    {
        return false;
    }

  private:
    std::vector<std::string> tile_scripts;
    int selected_tile = -1;
    Tile *selected_tile_prototype;
    int new_instance_dims[2] = {DEFAULT_NEW_INSTANCE_SIZE,DEFAULT_NEW_INSTANCE_SIZE};

};

#endif