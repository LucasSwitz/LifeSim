#include "imgui.h"
#include <stdarg.h>
#include <iostream>
struct Log
{
    ImGuiTextBuffer Buf;
    ImGuiTextFilter Filter;
    ImVector<int> LineOffsets; // Index to lines offset
    bool ScrollToBottom = true;


    Log()
    {
        
    }
    void Clear()
    {
        Buf.clear();
        LineOffsets.clear();
    }

    void AddLog(const char *fmt, ...) IM_PRINTFARGS(2)
    {
        va_list args;
        AddLog(fmt,args);
    }

    void AddLog(const char *fmt, va_list& args)
    {
        int old_size = Buf.size();
        Buf.appendv(fmt, args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size);
        ScrollToBottom = true;

        va_end(args);
    }

    int BufSize()
    {
        return Buf.size();
    }

    void Draw(const char *title, bool *p_opened = NULL)
    {
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
        ImGui::Begin(title, p_opened);
        if (ImGui::Button("Clear"))
            Clear();
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        Filter.Draw("Filter", -100.0f);
        ImGui::Separator();
        ImGui::BeginChild("scrolling");
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
        
        if (copy)
            ImGui::LogToClipboard();

        if (Filter.IsActive())
        {
            std::cout << Buf.c_str() << std::endl;
            const char *buf_begin = Buf.begin();
            const char *line = buf_begin;
            for (int line_no = 0; line != NULL; line_no++)
            {
                const char *line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
                if (Filter.PassFilter(line, line_end))
                    ImGui::TextUnformatted(line, line_end);
                line = line_end && line_end[1] ? line_end + 1 : NULL;
            }
        }
        else
        {
            ImGui::TextUnformatted(Buf.begin());
        }

        if (ScrollToBottom)
            ImGui::SetScrollHere(1.0f);
        ScrollToBottom = false;
        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::End();
    }
};