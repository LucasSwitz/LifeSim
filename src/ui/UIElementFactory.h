#ifndef UIELEMENTFACTORY_H
#define UIELEMENTFACTORY_H

#include "src/utils/json/json.hpp"
#include "src/utils/ResourceFactory.h"
#include "src/ui/LuaUIElement.h"

/**
    Factory for creating ui elements.
**/

using json = nlohmann::json;
class UIElementFactory : public ResourceFactory<std::string>
{

  public:
    UIElement *GetUIElement(std::string name)
    {
        if (!PrototypeExists(name))
        {
            throw AssetNotFoundException("UIElement: " + name);
        }

        LuaUIElement *new_ui_element = new LuaUIElement(-1, name);
        new_ui_element->LoadScript(LUA_STATE, _ui_element_files.at(name), name);
        return new_ui_element;
    }

    virtual void PopulateFactory(std::string search_directory, bool reset = false)
    {
        FileCrawler crawler;
        crawler.Crawl(search_directory, _ui_element_files);

        for (auto it = _ui_element_files.begin(); it != _ui_element_files.end();)
        {
            size_t pos = it->first.find(".lua");
            std::string no_ext = it->first.substr(0, pos);
            _ui_element_files[no_ext] = it->second;
            it = _ui_element_files.erase(it);
        }
    }

    static UIElementFactory *Instance()
    {
        static UIElementFactory instance("UIElement");
        return &instance;
    }

    bool PrototypeExists(std::string name)
    {
        return _ui_element_files.find(name) != _ui_element_files.end();
    }

    void Reset() override
    {
        _ui_element_files.clear();
    }

    std::unordered_map<std::string, std::string> const &GetAllUIElementBindings()
    {
        return _ui_element_files;
    }

    ptr<UIElement> FromJson(const json &element_json)
    {
        const std::string type = element_json["type"];

        if (uie_type_map.at(type) == UIELEMENT_CONTAINER)
        {
            Container* container = new Container();
            container->FromJson(element_json);
            ptr<UIElement> el(container);
            UIElement::FromJson(el, element_json);
            json children_arr = element_json["children"];
            for (auto it = children_arr.begin(); it != children_arr.end(); it++)
            {
                container->AddChild(UIElementFactory::FromJson(*it));
            }
            return el;
        }
        else
        {
            ptr<UIElement> e = UIElement::FromJson(uie_type_map.at(type), element_json);
            return e;
        }
    }

  private:
    UIElementFactory(std::string type) : ResourceFactory<std::string>(type){};
    std::unordered_map<std::string, std::string> _ui_element_files;
};

#endif