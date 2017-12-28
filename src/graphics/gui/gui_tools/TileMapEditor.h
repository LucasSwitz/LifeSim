#ifndef TILEMAPEDITOR_H
#define TILEMAPEDITOR_H

#include "src/graphics/gui/TextureCache.h"
#include "src/world/tile/LuaTileFactory.h"
#include "src/world/tile/Tile.h"
#include "src/graphics/gui/brush/PaintTileBrushState.h"
#include "src/graphics/gui/brush/Brush.h"

class TileMapEditor
{
  public:
    TileMapEditor()
    {
         
    }

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

    void Draw(TextureCache &texture_cache, Brush& brush)
    {
        ImGui::ListBoxVector("##TileEditorLBV", &selected_tile, tile_scripts);
        if (selected_tile != -1)
        {
            if(!selected_tile_prototype || selected_tile_prototype->GetName() != tile_scripts.at(selected_tile))
            {
                Tile* tile = LuaTileFactory::Instance()->GetTile(tile_scripts.at(selected_tile));
                selected_tile_prototype = ptr<Tile>(tile);
                brush.SetState(ptr<BrushState>(new PaintTileBrushState(selected_tile_prototype)));
            }

            std::string texture_path = selected_tile_prototype->GetComponentValueString("Graphics", "sprite");

            ptr<sf::Texture> texture = texture_cache.GetTexture(texture_path);
            ImGui::Image(*texture, sf::Vector2f(2 * TILE_WIDTH, 2 * TILE_HEIGHT));

            ImGui::SameLine();
            _component_editor.Draw(*selected_tile_prototype);
        }
    }

    std::string GetSelectedTexturePath()
    {
        if (selected_tile_prototype)
            return selected_tile_prototype->GetComponentValueString("Graphics", "sprite");
        else
            return "";
    }

  private:
    ComponentUserEditor _component_editor;
    std::vector<std::string> tile_scripts;
    ptr<Tile> selected_tile_prototype = nullptr;
    int selected_tile = -1;
};
#endif