#ifndef SAVE_DIALOG
#define SAVE_DIALOG

#include "imgui.h"
#include <string>

class InputDialog
{
    public:
    std::string Draw()
    {
        
        ImGui::InputText("Name##InputDialog", buf, 256);
        _focused = ImGui::IsRootWindowOrAnyChildHovered();
        ImGui::SameLine();


        if(ImGui::Button("Done##InputDialog"))
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