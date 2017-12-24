#ifndef UI_H
#define UI_H

#include "src/ui/Container.h"

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

    void Draw(PMIDGWindow &window);

    void GetAllElementsOfType(int type, std::list<ptr<UIElement>> &lst);

    virtual void AddToRootContainer(int id, ptr<UIElement> e);

    bool HasRootElement(int id);

  private:
    std::unordered_map<int, ptr<UIElement>> _root_elements;
};

#endif