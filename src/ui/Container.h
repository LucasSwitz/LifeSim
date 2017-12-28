#ifndef CONTAINER_H
#define CONTAINER_H

#include <list>
#include "src/ui/Layout.h"
#include "src/utils/math/Geometry.h"

class Container : public UIElement, public std::enable_shared_from_this<Container>
{
  public:
    Container(int x = 0, int y = 0, std::string name = "") : UIElement(UIELEMENT_CONTAINER, name, x, y)
    {
    }

    void SetLayout(ptr<Layout> layout)
    {
        _layout = layout;
    }

    void AddChild(ptr<UIElement> e)
    {
        _name_to_id_map[e->Name()] = e->ID();
        children[e->ID()] = e;
    }

    void Draw(PMIDGWindow &window) override
    {
        DoFormat();

        for (auto it = children.begin(); it != children.end(); it++)
        {
            it->second.get()->Draw(window);
        }
    }

    void DoFormat()
    {
        if (_layout)
            _layout->Format((int)GetComponentValueFloat("Position", "x"),
                            (int)GetComponentValueFloat("Position", "y"),
                            children);
    }

    ptr<UIElement> ChildAtPos(int x, int y) const
    {
        for (auto it = children.begin(); it != children.end(); it++)
        {
            auto child = it->second;
            int x_pos = child->GetComponentValueFloat("Position", "x");
            int y_pos = child->GetComponentValueFloat("Position", "y");
            int width = child->GetComponentValueFloat("Graphics", "width");
            int height = child->GetComponentValueFloat("Graphics", "height");

            if (ClickInBoundingBox(x, y, x_pos, y_pos, width, height))
            {
                if (child->Type() == UIELEMENT_CONTAINER)
                {
                    Container *child_container = dynamic_cast<Container *>(child.get());
                    return child_container->ChildAtPos(x, y);
                }
                else
                {
                    return child;
                }
            }
        }
        return nullptr;
    }

    void GetAllChildrenOfType(int type, std::list<ptr<UIElement>> &lst)
    {
        for (auto it = children.begin(); it != children.end(); it++)
        {
            auto child = it->second;
            if (child->Type() == type)
            {
                lst.push_back(child);
            }

            if (child->Type() == UIELEMENT_CONTAINER)
            {
                Container *cont = dynamic_cast<Container *>(child.get());
                cont->GetAllChildrenOfType(type, lst);
            }
        }
    }

    bool HasChild(int id)
    {
        return children.find(id) != children.end();
    }

    bool HasChild(const std::string& name)
    {
        return HasChild(_name_to_id_map[name]);
    }

    ptr<UIElement> GetChild(const std::string& name)
    {
        return GetChild(_name_to_id_map[name]);
    }

    ptr<UIElement> GetChild(int id)
    {
        if(HasChild(id))
            return children[id];
        throw UIElementException("Container: " + name + \
            " does not have child with id: " + std::to_string(id));
    }

    void Hide()
    {
        for (auto it = children.begin(); it != children.end(); it++)
        {
            it->second->Hide();
        }
    }

    void Show()
    {
        for (auto it = children.begin(); it != children.end(); it++)
        {
            it->second->Show();
        }
    }

  protected:
    std::unordered_map<int, ptr<UIElement>> children;
    std::unordered_map<std::string,int> _name_to_id_map;

  private:
    ptr<Layout> _layout = nullptr;
};
#endif