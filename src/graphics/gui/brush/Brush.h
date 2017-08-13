#ifndef BRUSH_H
#define BRUSH_H

#include "src/graphics/gui/brush/BrushState.h"
#include "src/graphics/gui/PMIDGWindow.h"
#include "src/world/stage/Instance.h"

class Brush
{
  public:
    void PaintWindow(PMIDGWindow &window)
    {
        if (_state)
        {
            if(_state->PaintWindow(window))
                _state = nullptr;
        }

    }


    bool OnInstanceMouseEvent(sf::Event &e, sf::Vector2f &event_world_position, Instance *instance, 
        ComponentUser* c = nullptr)
    {
        if (_state)
            return _state->OnInstanceMouseEvent(e, event_world_position, instance, c);
        return false;
    }

    bool OnKeyboardEvent(sf::Event &e, Instance *instance)
    {
        if (_state)
            return _state->OnKeyboardEvent(e, instance);
        return false;
    }

    void SetState(BrushState *state)
    {
        if (_state)
            delete _state;

        _state = state;
    }

    void DrawExtras()
    {
        if(_state)
            _state->DrawExtras();
    }

  private:
    BrushState *_state = nullptr;
};

#endif