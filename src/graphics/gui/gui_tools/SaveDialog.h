#ifndef SAVE_DIALOG
#define SAVE_DIALOG

class SaveDialog
{
    std::string Draw()
    {
        ImGui::InputText("Name");
        if(ImGui::Button("Save"))
        {
            //return filename;
        }
    }
};
#endif