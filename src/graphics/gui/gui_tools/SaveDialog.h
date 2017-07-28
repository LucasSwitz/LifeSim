#ifndef SAVE_DIALOG
#define SAVE_DIALOG

#include "imgui.h"
#include <string>

class SaveDialog
{
    public:
    std::string Draw()
    {
        
        ImGui::InputText("Name##SaveDialog", buf, 256);
        _focused = ImGui::IsRootWindowOrAnyChildHovered();
        ImGui::SameLine();


        if(ImGui::Button("Save##SaveDialog"))
        {
            return std::string(buf);
        }

        return "";
    }

    bool IsFocused()
    {
        return _focused;
    }

    private:
    bool _focused = false;
    char buf[256] = {};        
};
#endif