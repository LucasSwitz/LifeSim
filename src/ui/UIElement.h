#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "src/component/ComponentUser.h"
#include "src/ui/UIElementTypes.h"
#include "src/graphics/gui/TBWindow.h"

class UIElement : public ComponentUser
{
  friend class UIElementFactory;

public:
  struct UIElementException : public std::exception
  {
    std::string _msg;
    UIElementException(const std::string &msg) : _msg(msg) {}
    const char *what() const throw()
    {
      return _msg.c_str();
    }
  };
  struct Padding
  {

    Padding(int _left = 0, int _right = 0, int _top = 0, int _bottom = 0) : left(_left),
                                                                            right(_right),
                                                                            top(_top),
                                                                            bottom(_bottom){};
    int left;
    int right;
    int top;
    int bottom;
  };

  UIElement(int type_, std::string _name = "", int x = 0, int y = 0);

  void SetPadding(int left, int right, int top, int bottom);

  void SetPos(int x, int y);

  void SetX(int x);

  void SetY(int y);

  int Type();

  void Show();

  void Hide();

  virtual void Draw(TBWindow &window);

  UIElement *Clone();

  std::string Name();

protected:
  static ptr<UIElement> FromJson(int type, const nlohmann::json &json);
  static void FromJson(ptr<UIElement> e, const nlohmann::json &json);

  Padding padding;
  int id;
  int type;
  std::string name;
};
#endif