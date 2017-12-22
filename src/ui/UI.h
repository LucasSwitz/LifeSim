#ifndef UI_H
#define UI_H

#include "src/ui/UIElement.h"


class UI 
{
    public:
        void AddRootElement(ptr<UIElement> e)
        {
            _root_elements[e->ID()] = e;
        }

        void Draw(PMIDGWindow& window)
        {
            for(auto it = _root_elements.begin(); it != _root_elements.end(); it++)
            {
                it->second->Draw(window);
            }
        }

        void GetAllElementsOfType(int type, std::list<ptr<UIElement>>& lst)
        {
            for(auto it = _root_elements.begin(); it != _root_elements.end(); it++)
            {
                auto el = it->second;
                if(el->Type() == type)
                    lst.push_back(el);

                if(el->Type() == UIELEMENT_CONTAINER)
                {
                    Container* cont = dynamic_cast<Container*>(el.get());
                    cont->GetAllChildrenOfType(type,lst);
                }
            }
        }

    private:
        std::unordered_map<int, ptr<UIElement>> _root_elements;
};

#endif