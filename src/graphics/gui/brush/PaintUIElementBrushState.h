#ifndef PAINTUIELEMENTBRUSHSTATE_H
#define PAINTUIELEMENTBRUSHSTATE_H

#include "src/graphics/gui/brush/BrushState.h"
#include "src/ui/Container.h"
#include "src/ui/UIElement.h"

class PaintUIElementBrushState : public BrushState
{

  public:
    PaintUIElementBrushState(UIElement *prototype) : _prototype(prototype)
    {
    }

    bool OnUIMouseEvent(sf::Event &e, sf::Vector2f &event_world_position, ptr<UIElement> el,
                        ptr<ComponentUser> c = nullptr) override
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                if (el->Type() == UIELEMENT_CONTAINER)
                {
                    Container* container = dynamic_cast<Container*>(el.get());
                    UIElement *e = _prototype->Clone();
                    e->SetComponentValueFloat("Position", "x", event_world_position.x);
                    e->SetComponentValueFloat("Position", "y", event_world_position.y);
                    container->AddChild(ptr<UIElement>(e));
                }
            }
        }
    }

      private:
        ptr<UIElement> _prototype;
    };
#endif