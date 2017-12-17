#ifndef BRUSH_H
#define BRUSH_H

#include "src/graphics/gui/brush/BrushState.h"
#include "src/graphics/gui/PMIDGWindow.h"
#include "src/game/GameState.h"

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


    bool OnGameStateMouseEvent(sf::Event &e, sf::Vector2f &event_world_position, ptr<GameState> gs, 
        ptr<ComponentUser> c = nullptr)
    {
        if (_state)
            return _state->OnGameStateMouseEvent(e, event_world_position, gs, c);
        return false;
    }

    bool OnKeyboardEvent(sf::Event &e, ptr<GameState> gs)
    {
        if (_state)
            return _state->OnKeyboardEvent(e, gs);
        return false;
    }

    void SetState(ptr<BrushState> state)
    {
        _state = state;
    }

    void DrawExtras()
    {
        if(_state)
            _state->DrawExtras();
    }

  private:
    ptr<BrushState> _state = nullptr;
};

#endif