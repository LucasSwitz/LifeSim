#ifndef UI_H
#define UI_H

#include "src/ui/Container.h"
#include "src/ui/UIElementFactory.h"
#include "src/utils/json/json.hpp"
#include <fstream>

class UI
{
  public:
    struct InvalidElement : public std::exception
    {
        std::string _msg;
        InvalidElement(const std::string &msg) : _msg(msg) {}
        const char *what() const throw()
        {
            return _msg.c_str();
        }
    };
    void AddRootElement(ptr<UIElement> e);

    void Draw(TBWindow &window);

    void GetAllElementsOfType(int type, std::list<ptr<UIElement>> &lst);

    virtual void AddToRootContainer(int id, ptr<UIElement> e);

    bool HasRootElement(int id);

    virtual void AddToRootContainer(const std::string &name, ptr<UIElement> e);

    bool HasRootElement(const std::string &name);

    virtual void Show();

    virtual void Hide();

    void Load(const std::string &file_path);

    bool HasElement(const std::string &name);

    bool HasElement(int id);

    ptr<UIElement> GetElement(const std::string &name);

    ptr<UIElement> GetElement(int id);

  private:
    std::unordered_map<int, ptr<UIElement>> _root_elements;
    std::unordered_map<std::string, int> _name_to_id_map;
    std::string _name;
};

#endif