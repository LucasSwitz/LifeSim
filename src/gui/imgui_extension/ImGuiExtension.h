#include <vector>
#include "imgui.h"
#include <string>

namespace ImGui
{
    bool ListBoxVector(const char* label, int* currIndex, std::vector<std::string>& values);
};
