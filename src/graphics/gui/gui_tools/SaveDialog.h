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
        ImGui::SameLine();

        if(ImGui::Button("Save##SaveDialog"))
        {
            return std::string(buf);
        }

        return "";
    }

    private:
    char buf[256] = {};        
};
#endif