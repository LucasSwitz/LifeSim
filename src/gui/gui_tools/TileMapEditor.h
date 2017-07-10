#ifndef TILEMAPEDITOR_H
#define TILEMAPEDITOR_H

#include "imgui.h"
#include <stdarg.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "src/world/tile/LuaTileFactory.h"
#include "src/gui/imgui_extension/ImGuiExtension.h"
#include "src/world/tile/Tile.h"
#include "src/gui/TextureCache.h"

struct TileMapEditor
{
    std::vector<std::string> tile_scripts;
    int selected_tile = -1;
    Tile* selected_tile_prototype;
    std::vector<sf::Shape> _borders;

    template<typename IterableContainer>
    void SetTileList(const IterableContainer& scripts)
    {
        tile_scripts.clear();

        for(auto script : scripts)
        {
            tile_scripts.push_back(script);
        }
    }

    void SetTileList(const std::unordered_map<int, std::string>& scripts)
    {
        tile_scripts.clear();

        for(auto it = scripts.begin(); it != scripts.end(); it++)
        {
            tile_scripts.push_back(it->second);
        }
    }

    void Draw(const char *title, TextureCache& texture_cache, sf::RenderWindow& render_window, bool *p_opened = NULL)
    {
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
        ImGui::Begin(title, p_opened);
        ImGui::ListBoxVector("Tiles", &selected_tile, tile_scripts);

        if(selected_tile != -1)
        {
            selected_tile_prototype = LuaTileFactory::Instance()->GetTile(tile_scripts.at(selected_tile));
            std::string texture_path = selected_tile_prototype->GetComponentValueString("Graphics","sprite");
             
            ImGui::LabelText("Path: ",texture_path.c_str());

            ImGui::Image(*texture_cache.GetTexture(texture_path));
            //find some way to edit other components
        }
        ImGui::End();
    }

    void OnClickEvent(int x, int y)
    {
        if(selected_tile != -1)
        {
            Tile* tile = GameRunner::Instance()->GetCurrentStage()->GetCurrentInstance()->GetTileMap()->TileAt(x,y);
            std::string selected_texture = selected_tile_prototype->GetComponentValueString("Graphics","sprite");
            tile.SetComponentValueString("Graphics","sprite",selected_texture.c_str());
        }
    }

    void DrawBorders(sf::RenderWindow& render_window)
    {
        for(sf::Shape& border : borders)
        {
            render_window.Draw(border);
        }
    }
    void SaveTileMap(TileMap* map, std::string map_path)
    {
        
    }
};

#endif