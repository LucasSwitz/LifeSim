#ifndef CONTROLLERSYSTEM_H
#define CONTROLLERSYSTEM_H

#include "src/system/System.h"
#include "src/controllers/ControllerBase.h"

class ControllersSystem : public System
{
    public:
    virtual void Update(float seconds_since_last_update, ptr<GameState> game_state)
    {
        auto& controllers = ControllerBase::Instance()->GetAll();

        for(auto it = controllers.begin(); it != controllers.end(); it++)
        {
            it->second->Poll();
        }
    }   
};
#endif