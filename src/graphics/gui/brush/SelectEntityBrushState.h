#ifndef SELECTENITITYBRUSHSTATE_H
#define SELECTENITITYBRUSHSTATE_H

#include "src/game_objects/Entity.h"
#include "src/graphics/gui/brush/BrushState.h"

class SelectEntityBrushState : public BrushState
{
  public:
    enum SelectionState
    {
        RELEASED,
        MOVING
    };

    SelectEntityBrushState(Entity *selected) : _selected(selected)
    {

    }

    void MoveEntity(PMIDGWindow &window)
    {
        if (_selected)
        {
            sf::Vector2i screen_mouse_position = sf::Mouse::getPosition(window.SFWindow());
            sf::Vector2f world_mouse_position = window.SFWindow().mapPixelToCoords(screen_mouse_position);

            _selected->SetComponentValueFloat("Position", "x", world_mouse_position.x);
            _selected->SetComponentValueFloat("Position", "y", world_mouse_position.y);
        }
    }

    bool PaintWindow(PMIDGWindow &window) override
    {
        switch (_selection_state)
        {
        case RELEASED:
            return true;
        case MOVING:
            MoveEntity(window);
            return false;
        }
    }

    bool OnInstanceMouseEvent(sf::Event &e, sf::Vector2f &event_world_position, Instance *instance) override
    {
        if (_selected)
        {
            if (e.type == sf::Event::MouseButtonPressed)
            {
                _selection_state = MOVING;
                return false;
            }
            else if (e.type == sf::Event::MouseButtonReleased)
            {
                _selection_state = RELEASED;
                return true;
            }
        }
    }

    bool OnKeyboardEvent(sf::Event &e, Instance *instance) override
    {
        if (_selected)
        {
            if (e.key.code == sf::Keyboard::Delete)
            {
                delete _selected;
                _selected = nullptr;
            }
        }
    }

  private:
    Entity *_selected = nullptr;
    SelectionState _selection_state;
};

#endif