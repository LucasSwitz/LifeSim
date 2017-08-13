#ifndef CURRENTSELECTIONWINDOW_H
#define CURRENTSELECTIONWINDOW_H

#include "imgui.h"
#include "src/component/ComponentUser.h"
#include "src/graphics/gui/gui_tools/ComponentUserEditor.h"

struct CurrentSelectionWindow
{
    void Draw(ComponentUser* current_selection)
    {
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("Selected");
        selection_editor.Draw(*current_selection);
        ImGui::End();
    }
    
    bool IsFocused()
    {
        return _focused;
    }

    private:
        bool _focused = false;
        ComponentUserEditor selection_editor;
};
#endif
