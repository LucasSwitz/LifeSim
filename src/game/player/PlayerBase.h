#ifndef PLAYERBASE_H
#define PLAYERBASE_H

#include "src/controllers/ControllerBase.h"
#include "src/controllers/ControllerFactory.h"

class PlayerBase : public ComponentUserBaseSubscriber
{

    public:
        PlayerBase()
        {
        }

        void OnEvent(ComponentUserBaseEvent& e)
        {
            ComponentUser* player = e.user;
            ptr<Component> player_component = player->GetComponent("Player");
            int controller_id = player_component->GetFloatValue("controller_id");
            
            //Create controller for player if controller doesn't already exist
            if(!ControllerBase::Instance()->HasControllerWithID(controller_id))
            {   
                int controller_type = player_component->GetFloatValue("controller_type");
                Controller* controller = ControllerFactory::GetController(controller_type, controller_id);
                ControllerBase::Instance()->AddController(controller);
            }
        }
};
#endif
