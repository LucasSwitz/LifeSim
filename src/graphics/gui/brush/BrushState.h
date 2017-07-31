#ifndef BRUSHSTATE_H
#define BRUSHSTATE_H

#include <SFML/System/Vector2.hpp>


#include "src/graphics/gui/PMIDGWindow.h"
#include "src/world/stage/Instance.h"

class BrushState
{
  public:
    virtual bool OnKeyboardEvent(sf::Event& e,Instance* instance){};
    virtual bool OnInstanceMouseEvent(sf::Event& e, sf::Vector2f& event_world_position, Instance* instance){};
    virtual bool PaintWindow(PMIDGWindow& window) {return false;};
};
#endif