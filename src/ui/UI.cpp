#include "src/ui/UI.h"

void UI::AddRootElement(ptr<UIElement> e)
{
    _name_to_id_map[e->Name()] = e->ID();
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
    if (HasRootElement(id))
    {
        if (e->Type() != UIELEMENT_CONTAINER)
            throw InvalidElement("Element " + std::to_string(id) + " is not a container");

        Container *c = dynamic_cast<Container *>(_root_elements[id].get());
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

void UI::Show()
{
    for (auto it = _root_elements.begin(); it != _root_elements.end(); it++)
    {
        it->second->Show();
    }
}

void UI::Hide()
{
    for (auto it = _root_elements.begin(); it != _root_elements.end(); it++)
    {
        it->second->Hide();
    }
}

void UI::AddToRootContainer(const std::string &name, ptr<UIElement> e)
{
    AddToRootContainer(_name_to_id_map[name], e);
}

bool UI::HasRootElement(const std::string &name)
{
    HasRootElement(_name_to_id_map[name]);
}

void UI::Load(const std::string &file_path)
{
    using json = nlohmann::json;

    std::ifstream input(file_path);
    json ui_json;
    input >> ui_json;

    _name = ui_json["name"];
    json elements = ui_json["elements"];

    for (auto it = elements.begin(); it != elements.end(); it++)
    {
        json element = *it;
        ptr<UIElement> e = UIElementFactory::Instance()->FromJson(element);
        AddRootElement(e);
    }
}

bool UI::HasElement(const std::string &name)
{
    for (auto it = _root_elements.begin(); it != _root_elements.end(); it++)
    {
        ptr<UIElement> el = it->second;
        if (el->Name().compare(name) == 0)
            return true;
        else if (el->Type() == UIELEMENT_CONTAINER)
        {
            Container *cont = dynamic_cast<Container *>(el.get());
            if (cont->HasChild(name))
                return true;
        }
    }
}

bool UI::HasElement(int id)
{
    for (auto it = _root_elements.begin(); it != _root_elements.end(); it++)
    {
        ptr<UIElement> el = it->second;
        if (el->ID() == id)
            return true;
        else if (el->Type() == UIELEMENT_CONTAINER)
        {
            Container *cont = dynamic_cast<Container *>(el.get());
            if (cont->HasChild(id))
                return true;
        }
    }
}

ptr<UIElement> UI::GetElement(const std::string &name)
{
    for (auto it = _root_elements.begin(); it != _root_elements.end(); it++)
    {
        ptr<UIElement> el = it->second;
        if (el->Name().compare(name) == 0)
            return el;
        else if (el->Type() == UIELEMENT_CONTAINER)
        {
            Container *cont = dynamic_cast<Container *>(el.get());
            if (cont->HasChild(name))
            {
                return cont->GetChild(name);
            }
        }
    }
}

ptr<UIElement> UI::GetElement(int id)
{
    for (auto it = _root_elements.begin(); it != _root_elements.end(); it++)
    {
        ptr<UIElement> el = it->second;
        if (el->ID() == id)
            return el;
        else if (el->Type() == UIELEMENT_CONTAINER)
        {
            Container *cont = dynamic_cast<Container *>(el.get());
            if (cont->HasChild(id))
            {
                return cont->GetChild(id);
            }
        }
    }
}