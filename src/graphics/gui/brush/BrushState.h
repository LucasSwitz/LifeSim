#ifndef BRUSHSTATE_H
#define BRUSHSTATE_H

#include <SFML/System/Vector2.hpp>

#include "src/graphics/gui/TBWindow.h"
#include "src/game/GameState.h"
#include "src/ui/Container.h"

class BrushState
{
  public:
    virtual bool OnKeyboardEvent(sf::Event &e, ptr<GameState> gs){};
    virtual bool OnGameStateMouseEvent(sf::Event &e, sf::Vector2f &event_world_position, ptr<GameState> gs,
                                       ptr<ComponentUser> c = nullptr){};
    virtual bool OnUIMouseEvent(sf::Event &e, sf::Vector2f &event_world_position, ptr<UIElement> el,
                                       ptr<ComponentUser> c = nullptr){};
    virtual bool PaintWindow(TBWindow &window) { return false; };
    virtual void DrawExtras(){};
};
#endif