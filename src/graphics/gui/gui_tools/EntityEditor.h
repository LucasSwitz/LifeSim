#ifndef ENTITYEDITOR_H
#define ENTITYEDITOR_H

#include "src/graphics/gui/TextureCache.h"
#include "src/game_objects/Entity.h"
#include "src/game_objects/LuaEntityFactory.h"
#include "src/graphics/gui/brush/PaintEntityBrushState.h"

#define BRUSH_STATE_ENTITY 1

class EntityEditor
{
  public:
    template <typename IterableContainer>
    void SetEntityList(const IterableContainer &scripts)
    {
        entity_scripts.clear();

        for (auto script : scripts)
        {
            entity_scripts.push_back(script);
        }
    }

    void SetEntityList(const std::unordered_map<int, std::string> &scripts)
    {
        entity_scripts.clear();

        for (auto it = scripts.begin(); it != scripts.end(); it++)
        {
            entity_scripts.push_back(it->second);
        }
    }

    void Draw(TextureCache &texture_cache, Brush& brush)
    {
        ImGui::ListBoxVector("##LBVEntityEditor", &selected_entity, entity_scripts);
        if (selected_entity != -1)
        {
            if(!selected_entity_prototype || selected_entity_prototype->GetPrototypeName().compare( 
                entity_scripts.at(selected_entity)) != 0){
                delete selected_entity_prototype;
                selected_entity_prototype = LuaEntityFactory::Instance()
                    ->GetEntityByName(entity_scripts.at(selected_entity));
                brush.SetState(ptr<BrushState>(new PaintEntityBrushState(selected_entity_prototype)));
            }

            if (selected_entity_prototype && selected_entity_prototype->HasComponent("Graphics")){
                std::string texture_path = selected_entity_prototype->GetComponentValueString("Graphics", "sprite");
                ptr<sf::Texture> texture = texture_cache.GetTexture(texture_path);
                ImGui::Image(*texture);
                ImGui::SameLine();
                
            }
            _component_editor.Draw(*selected_entity_prototype);
        }
    }

  private:
    ComponentUserEditor _component_editor;
    std::vector<std::string> entity_scripts;
    Entity *selected_entity_prototype = nullptr;
    int selected_entity = -1;
};
#endif