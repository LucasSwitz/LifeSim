#ifndef RELATIVELAYOUT_H
#define RELATIVELAYOUT_H

#include "src/ui/Layout.h"

/*anchor is top left*/

class RelativeLayout : public Layout
{
  public:
    RelativeLayout(int anchor_x, int anchor_y);

    void Format(int x_start, int y_start, std::unordered_map<int, ptr<UIElement>> &elements)
    {
        int rel_x = x_start + _anchor_x;
        int rel_y = y_start + _anchor_y;

        std::unordered_map<int, RelativeLayoutNode> formatted_cache;

        for (auto it = elements.begin(); it != elements.end(); it++)
        {
            auto e = it->second;
            if (formatted_cache.find(e->ID()) != formatted_cache.end())
                continue;

            Format(e, elements, formatted_cache);
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

    void FormatRightOfEdge(ptr<UIElement> child);

    void FormatBelowEdge(ptr<UIElement> child);

    void FormatRight(ptr<UIElement> child, RelativeLayoutNode &parent_node);

    void FormatBelow(ptr<UIElement> child, RelativeLayoutNode &parent_node);

    template <typename T>
    std::unordered_map<int, RelativeLayoutNode>::iterator Format(ptr<UIElement> el, T &elements, std::unordered_map<int, RelativeLayoutNode> &formatted)
    {
        auto descriptors = el->GetDescriptors();

        if (descriptors.find("right_of") != descriptors.end())
        {
            if (IsRelativeToLeftEdge(el))
            {
                FormatRightOfEdge(el);
            }
            else
            {
                int parent_id = std::stoi(descriptors["right_of"]);
                auto parent_it = formatted.find(parent_id);

                if (parent_it == formatted.end())
                    parent_it = Format(elements[parent_id], elements, formatted);

                FormatRight(el, parent_it->second);
                parent_it->second.right = el;
            }
            return (formatted.insert({el->ID(),RelativeLayoutNode(el)})).first;
        }
        else if (descriptors.find("below") != descriptors.end())
        {
            if (IsRelativeTopEdge(el))
            {
                FormatBelowEdge(el);
            }
            else
            {
                int parent_id = std::stoi(descriptors["below"]);
                auto parent_it = formatted.find(parent_id);
                if (parent_it == formatted.end())
                    parent_it = Format(elements[parent_id], elements, formatted);

                FormatBelow(el, parent_it->second);
                parent_it->second.below = el;
            }
            return (formatted.insert({el->ID(), RelativeLayoutNode(el)})).first;
        }
        else
            throw InvalidFormatException("No relative parent specified.");
    }
};

#endif