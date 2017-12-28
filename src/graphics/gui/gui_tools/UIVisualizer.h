#ifndef UIVISULIZER_H
#define UIVISULIZER_H

#include "src/ui/UI.h"
#include "src/ui/Container.h"

class UIVisualizer
{
  public:
    UIVisualizer(ptr<UI> ui) : _ui(ui)
    {
    }

    void Draw(PMIDGWindow &window)
    {
        std::list<ptr<UIElement>> containers;
        _ui->GetAllElementsOfType(UIELEMENT_CONTAINER, containers);

        for (ptr<UIElement> cont : containers)
        {
            int x = cont->GetComponentValueFloat("Position", "x");
            int y = cont->GetComponentValueFloat("Position", "x");
            int width = cont->GetComponentValueFloat("Graphics", "width");
            int height = cont->GetComponentValueFloat("Graphics", "height");

            sf::RectangleShape rect(sf::Vector2f(width, height));
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color::Black);
            rect.setOutlineThickness(2);
            rect.setPosition(x, y);
            window.DrawNow(rect);
        }
    }

  private:
    ptr<UI> _ui;
};
#endif