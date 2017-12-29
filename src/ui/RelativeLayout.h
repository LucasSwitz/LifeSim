#ifndef RELATIVELAYOUT_H
#define RELATIVELAYOUT_H

#include "src/ui/Layout.h"

/*anchor is top left*/

class RelativeLayout : public Layout
{
  public:
    void Format(int x_start, int y_start, std::unordered_map<std::string, ptr<UIElement>> &elements)
    {
        std::unordered_map<std::string, RelativeLayoutNode> formatted_cache;

        for (auto it = elements.begin(); it != elements.end(); it++)
        {
            auto e = it->second;
            if (formatted_cache.find(e->Name()) != formatted_cache.end())
                continue;

            Format(x_start, y_start, e, elements, formatted_cache);
        }
    }

  private:
    int _anchor_x;
    int _anchor_y;

    struct RelativeLayoutNode
    {
        RelativeLayoutNode(ptr<UIElement> p) : parent(p){};
        RelativeLayoutNode(){};

        ptr<UIElement> parent = nullptr;
        ptr<UIElement> right = nullptr;
        ptr<UIElement> below = nullptr;
    };

    bool IsRelativeToLeftEdge(ptr<UIElement> child);
    bool IsRelativeTopEdge(ptr<UIElement> child);

    void FormatRightOfEdge(int x, int y, ptr<UIElement> child);

    void FormatBelowEdge(int x, int y, ptr<UIElement> child);

    void FormatRight(ptr<UIElement> child, RelativeLayoutNode &parent_node);

    void FormatBelow(ptr<UIElement> child, RelativeLayoutNode &parent_node);

    template <typename T>
    std::unordered_map<std::string, RelativeLayoutNode>::iterator Format(int x_start, int y_start, ptr<UIElement> el, T &elements, std::unordered_map<std::string, RelativeLayoutNode> &formatted)
    {
        auto descriptors = el->GetComponent("UI");

        if (descriptors->HasStringValue("right_of"))
        {
            if (IsRelativeToLeftEdge(el))
            {
                FormatRightOfEdge(x_start, y_start, el);
            }
            else
            {
                std::string parent_id = descriptors->GetStringValue("right_of");
                auto parent_it = formatted.find(parent_id);

                if (parent_it == formatted.end())
                    parent_it = Format(x_start, y_start, elements[parent_id], elements, formatted);

                FormatRight(el, parent_it->second);
                parent_it->second.right = el;
            }
        }

        if (descriptors->HasStringValue("below"))
        {
            if (IsRelativeTopEdge(el))
            {
                FormatBelowEdge(x_start, y_start, el);
            }
            else
            {
                std::string parent_id = descriptors->GetStringValue("below");
                auto parent_it = formatted.find(parent_id);
                if (parent_it == formatted.end())
                    parent_it = Format(x_start, y_start, elements[parent_id], elements, formatted);

                FormatBelow(el, parent_it->second);
                parent_it->second.below = el;
            }
        }
        return (formatted.insert({el->Name(), RelativeLayoutNode(el)})).first;

        /*else
            throw InvalidFormatException("No relative parent specified for element: " + el->Name());*/
    }
};

#endif