#ifndef PLAYERBASE_H
#define PLAYERBASE_H

#include "src/controllers/ControllerBase.h"
#include "src/component/ComponentUserBase.h"
#include "src/controller/ControllerFactory.h"

class PlayerBase : public ComponentUserBaseSubscriber
{

    public:
        PlayerBase()
        {
            ComponentUserBase::Instance()->AddSubscriber(this,"Player");
        }

        void OnEvent(ComponentUserBaseEvent& e)
        {
            ComponentUser* player = e.user;
            Component* player_component = player->GetComponent("Player");
            int controller_id = player_component->GetFloatValue("controller");

            //Create controller for player if controller doesn't already exist
            if(!ControllerBase::Instance()->HasControllerWithID(controller_id))
            {   
                int controller_type = player_component->GetFloatValue("controller_type");
                Controller* controller = ControllerFactory::GetController(controller_type);
                ControllerBase::Instance()->AddController(controller);
            }
        }
};
#endif
