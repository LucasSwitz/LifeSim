#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "src/component/ComponentUser.h"
#include "src/ui/UIElementTypes.h"
#include "src/graphics/gui/PMIDGWindow.h"

class UIElement : public ComponentUser
{
  public:
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

    void SetDescriptor(const std::string k, const std::string value);

    void SetPos(int x, int y);

    void SetX(int x);

    void SetY(int y);

    int Type();

    virtual void Draw(PMIDGWindow& window);

    UIElement *Clone();

    std::string Name();

    const std::unordered_map<std::string,std::string>& GetDescriptors();
    
  protected:
    Padding padding;
    int id;
    int type;
    std::string name;
    std::unordered_map<std::string, std::string> descriptors;
};
#endif