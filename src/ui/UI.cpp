#include "src/ui/UI.h"

void UI::AddRootElement(ptr<UIElement> e)
{
    _root_elements[e->ID()] = e;
}

void UI::Draw(PMIDGWindow &window)
{
    for (auto it = _root_elements.begin(); it != _root_elements.end(); it++)
    {
        it->second->Draw(window);
    }
}

void UI::GetAllElementsOfType(int type, std::list<ptr<UIElement>> &lst)
{
    for (auto it = _root_elements.begin(); it != _root_elements.end(); it++)
    {
        auto el = it->second;
        if (el->Type() == type)
            lst.push_back(el);

        if (el->Type() == UIELEMENT_CONTAINER)
        {
            Container *cont = dynamic_cast<Container *>(el.get());
            cont->GetAllChildrenOfType(type, lst);
        }
    }
}

void UI::AddToRootContainer(int id, ptr<UIElement> e)
{
    if(HasRootElement(id)){
        if(e->Type() != UIELEMENT_CONTAINER)
            throw InvalidElement("Element " + std::to_string(id) + " is not a container");

        Container* c = dynamic_cast<Container*>(_root_elements[id].get());
        c->AddChild(e);
    }
    else
    {
        throw InvalidElement("No root element with id: " + std::to_string(id));
    }
}

bool UI::HasRootElement(int id)
{
    return _root_elements.find(id) != _root_elements.end();
}
