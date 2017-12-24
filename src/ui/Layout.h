#ifndef LAYOUT_H
#define LAYOUT_H

#include "src/ui/UIElement.h"
#include <list>

class Layout
{
public:
  struct InvalidFormatException : public std::exception
  {
    std::string _msg;
    InvalidFormatException(const std::string &msg) : _msg(msg) {}
    const char *what() const throw()
    {
      return _msg.c_str();
    }
  };

  virtual void Format(int x_start, int y_start,
                      std::unordered_map<int, ptr<UIElement>> &elements) {}
};
#endif