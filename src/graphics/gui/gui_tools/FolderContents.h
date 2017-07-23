#ifndef FOLDERCONTENTS_H
#define FOLDERCONTENTS_H

#include "imgui.h"
#include <string>
#include <experimental/filesystem>

using namespace std::experimental::filesystem;
class FolderContents
{
  public:
    FolderContents(const std::string &folder_path) : _folder_path(folder_path)
    {
    }
    std::string Draw()
    {
        std::vector<std::string> files;
        _filter.Draw("Search##Instance Filter");
        for (auto &current_dir : directory_iterator(_folder_path))
        {
            path current_path = current_dir.path();
            std::string file_name = current_path.filename();
            if(_filter.PassFilter(file_name.c_str()))
                files.push_back(file_name); 
        }
        ImGui::PushItemWidth(-1);
        ImGui::ListBoxVector("", &_selected_file, files);

        //if selection return file name
        ImGui::PopItemWidth();

    }

  private:
    std::string _folder_path;
    int _selected_file = -1;
    ImGuiTextFilter _filter;

};
#endif