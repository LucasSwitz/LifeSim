#ifndef PAINTCONTAINERBRUSHSTATE_H
#define PAINTCONTAINERBRUSHSTATE_H

#include "src/graphics/gui/brush/BrushState.h"
#include "src/utils/window/WindowUtils.h"

class PaintContainerBrushState : public BrushState
{
  public:
    enum PaintingState
    {
        DORMANT,
        PAINTING
    };

    bool PaintWindow(PMIDGWindow &window) override
    {
        if (_painting_state == PAINTING)
        {
            RenderContainerOutline(window);
        }
        return false;
    }

    bool OnUIMouseEvent(sf::Event &e, sf::Vector2f &event_world_position, ptr<UIElement> el,
                        ptr<ComponentUser> c = nullptr) override
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                _mouse_history.x1 = event_world_position.x;
                _mouse_history.y1 = event_world_position.y;
                _painting_state = PAINTING;
                return true;
            }
            else if (e.mouseButton.button == sf::Mouse::Right)
            {
                _painting_state = DORMANT;
                return true;
            }
        }
        else if (e.type == sf::Event::MouseButtonReleased)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                _mouse_history.x2 = event_world_position.x;
                _mouse_history.y2 = event_world_position.y;
                _painting_state = DORMANT;
                return true;
            }
        }
    }

  private:
    PaintingState _painting_state = DORMANT;
    MouseHistory _mouse_history;

    void RenderContainerOutline(PMIDGWindow &window)
    {
        sf::Vector2i screen_mouse_position = sf::Mouse::getPosition(window.SFWindow());
        sf::Vector2f world_mouse_position = window.SFWindow().mapPixelToCoords(screen_mouse_position);

        int current_mouse_position_x = world_mouse_position.x;
        int current_mouse_position_y = world_mouse_position.y;

        int delta_x = current_mouse_position_x - _mouse_history.x1;
        int delta_y = current_mouse_position_y - _mouse_history.y1;

        int width = std::abs(delta_x);
        int height = std::abs(delta_y);

        int pos_x = (delta_x < 0 ? current_mouse_position_x : _mouse_history.x1);
        int pos_y = (delta_y < 0 ? current_mouse_position_y : _mouse_history.y1);

        sf::RectangleShape rect(sf::Vector2f(width, height));
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color(255, 255, 255, 100));
        rect.setOutlineThickness(1);
        rect.setPosition(pos_x, pos_y);
        window.DrawNow(rect);
    }
};
#endif