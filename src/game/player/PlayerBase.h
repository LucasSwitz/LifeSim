#ifndef PLAYERBASE_H
#define PLAYERBASE_H

#include "src/controllers/ControllerBase.h"
#include "src/controllers/ControllerFactory.h"
#include "src/event/EventManager.h"

class PlayerBase : public ComponentUserBaseSubscriber
{

  public:
    PlayerBase(EventManager &evm) : _evm(evm)
    {

    }

    void OnEvent(ComponentUserBaseEvent &e)
    {
        ComponentUser *player = e.user;
        ptr<Component> player_component = player->GetComponent("Player");
        int controller_id = player_component->GetFloatValue("controller_id");

        //Create controller for player if controller doesn't already exist
        if (!ControllerBase::Instance()->HasControllerWithID(controller_id))
        {
            int controller_type = player_component->GetFloatValue("controller_type");
            Controller *controller = ControllerFactory::GetController(_evm, controller_type, controller_id);
            ControllerBase::Instance()->AddController(controller);
        }
    }
private:
    EventManager& _evm;
};
#endif
