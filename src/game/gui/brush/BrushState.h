#ifndef BRUSHSTATE_H
#define BRUSHSTATE_H

#include <SFML/System/Vector2.hpp>


#include "src/game/gui/PMIDGWindow.h"
#include "src/world/stage/Instance.h"

class BrushState
{
  public:
    virtual bool OnInstanceMouseEvent(sf::Event& e, sf::Vector2f& event_world_position, Instance* instance) = 0;
    virtual void PaintWindow(PMIDGWindow& window) {}
};
#endif