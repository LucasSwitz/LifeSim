#ifndef UIELEMENTFACTORY_H
#define UIELEMENTFACTORY_H

#include "src/utils/ResourceFactory.h"
#include "src/ui/UIElement.h"

/**
    Factory for creating ui elements.
**/

class UIElementFactory : public ResourceFactory<std::string>
{
  public:
    virtual void AddResource(Preamble &pre, std::string script_path) override
    {
        std::string prototype_name = pre.GetFlag("Name");
        _ui_element_files.insert(std::make_pair(prototype_name, script_path));
    };

    UIElement* GetUIElement(std::string name)
    {
        if (!PrototypeExists(name))
        {
            throw AssetNotFoundException("UIElement: " + name);
        }
        /*
         * Somehow parse this.
         * 
         */
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

    std::unordered_map<std::string, std::string> const & GetAllUIElementBindings()
    {
        return _ui_element_files;
    }

  private:
    UIElementFactory(std::string type) : ResourceFactory<std::string>(type){};
    std::unordered_map<std::string, std::string> _ui_element_files;
};

#endif