#ifndef PAINTENTITYBRUSHSTATE_H
#define PAINTENTITYBRUSHSTATE_H

#include "src/event/messaging/MessageDispatch.h"
#include "src/graphics/gui/brush/BrushState.h"
#include "src/game_objects/Entity.h"

class PaintEntityBrushState : public BrushState
{

    public:
    PaintEntityBrushState(Entity* prototype) : _prototype(prototype)
    {

    }

    bool OnInstanceMouseEvent(sf::Event& e, sf::Vector2f& event_world_position, Instance* instance, 
        ComponentUser* c = nullptr) override
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                Entity *e = _prototype->Clone();
                e->SetComponentValueFloat("Position", "x", event_world_position.x);
                e->SetComponentValueFloat("Position", "y", event_world_position.y);
                Event event(EventType::SPAWN_ENTITY_EVENT,-1,instance->GetID(),e);
                MessageDispatch::Instance()->LaunchEvent(event);
            }
            return true;
        }
    }

    private:
        Entity* _prototype;
};
#endif