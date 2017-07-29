#ifndef PAINTENTITYBRUSHSTATE_H
#define PAINTENTITYBRUSHSTATE_H

#include "src/graphics/gui/brush/BrushState.h"
#include "src/game_objects/Entity.h"

class PaintEntityBrushState : public BrushState
{

    public:
    PaintEntityBrushState(Entity* prototype) : _prototype(prototype)
    {

    }

    bool OnInstanceMouseEvent(sf::Event& e, sf::Vector2f& event_world_position, Instance* instance) override
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                Entity *e = _prototype->Clone();
                e->SetComponentValueFloat("Position", "x", event_world_position.x);
                e->SetComponentValueFloat("Position", "y", event_world_position.y);
                EntityManager::Instance()->RegisterEntity(e);
            }
            return true;
        }
    }

    private:
        Entity* _prototype;
};
#endif