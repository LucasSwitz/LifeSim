#ifndef STAGEEDITOR_H
#define STAGEEDITOR_H

#include "src/graphics/gui/TextureCache.h"
#include "src/world/stage/Stage.h"

class StageEditor
{
  public:
    StageEditor()
    {
    }

    void Draw(Stage *stage)
    {
        if (!stage)
            return;
        ImGui::Begin("Stage Editor");

        _instance_ids.clear();
        const std::unordered_map<int, Instance *> instance_map = stage->GetInstances();
        for (auto it = instance_map.begin(); it != instance_map.end(); it++)
        {
            _instance_ids.push_back(std::to_string(it->first));
        }

        ImGui::ListBoxVector("", &_selected_instance, _instance_ids);

        if (_selected_instance != -1 && _last_selection != _selected_instance)
        {
            _last_selection = _selected_instance;
            stage->ChangeInstance(std::stoi(_instance_ids[_selected_instance])); //fix this to accept ints
        }

        ImGui::End();
    }

  private:
    std::vector<std::string> _instance_ids;
    int _selected_instance = -1;
    int _last_selection = -1;
};
#endif