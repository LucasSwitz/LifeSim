#ifndef BRUSHSTATE_H
#define BRUSHSTATE_H

#include <SFML/System/Vector2.hpp>


#include "src/graphics/gui/PMIDGWindow.h"
#include "src/game/GameState.h"

class BrushState
{
  public:
    virtual bool OnKeyboardEvent(sf::Event& e, GameState* gs){};
    virtual bool OnGameStateMouseEvent(sf::Event& e, sf::Vector2f& event_world_position, GameState* gs, 
        ComponentUser* c = nullptr){};
    virtual bool PaintWindow(PMIDGWindow& window) {return false;};
    virtual void DrawExtras(){};
};
#endif