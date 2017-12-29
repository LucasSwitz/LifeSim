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

    void Draw(ptr<Stage> stage)
    {
        if (!stage)
            return;

        ImGui::Begin("Stage Editor");
        _focused = ImGui::IsRootWindowOrAnyChildHovered();

        _instance_names.clear();
        auto& instance_map = stage->GetInstances();
        for (auto it = instance_map.begin(); it != instance_map.end(); it++)
        {
            _instance_names.push_back(it->first);
        }
            
        ImGui::ListBoxVector("", &_selected_instance, _instance_names);

        if (_last_stage != stage)
        _selected_instance = -1;

        if (_selected_instance != -1 && (_last_selection != _selected_instance))
        {
            _last_selection = _selected_instance;
            stage->ChangeInstance(_instance_names[_selected_instance]);
        }


        _last_stage = stage;
        ImGui::End();
    }

    bool IsFocused()
    {
        return _focused;
    }

  private:
    std::vector<std::string> _instance_names;
    int _selected_instance = -1;
    int _last_selection = -1;
    bool _focused = false;
    ptr<Stage> _last_stage = 0;
};
#endif