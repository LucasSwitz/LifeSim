#ifndef CONTROLLERSYSTEM_H
#define CONTROLLERSYSTEM_H

#include "src/system/SystemFactory.h"
#include "src/system/System.h"
#include "src/controllers/ControllerBase.h"

class Engine;

class ControllersSystem : public System<Engine>
{
    public:
    virtual void Update(float seconds_since_last_update, Engine* e)
    {
        auto& controllers = ControllerBase::Instance()->GetAll();

        for(auto it = controllers.begin(); it != controllers.end(); it++)
        {
            it->second->Poll();
        }
    }   
};
#endif