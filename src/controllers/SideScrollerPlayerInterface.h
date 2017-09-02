#ifndef SIDESCROLLERPLAYERINTERFACE_H
#define SIDESCROLLERPLAYERINTERFACE_H

#include "src/controllers/Controller.h"

class SideScrollerPlayerInterface : public Controller
{
    public:
    SideScrollerPlayerInterface(int id) : Controller(id){};
    virtual bool Jump() = 0; 
    virtual bool Left() = 0; 
    virtual bool Right() = 0; 
    virtual bool Action() = 0; 

    static SideScrollerPlayerInterface* Downcast(Controller* controller)
    {
        SideScrollerPlayerInterface* interface = dynamic_cast<SideScrollerPlayerInterface*>(controller);

        if(interface)
            return interface;
        else
        {
            std::cout << "Invalid Downcast to SideScollerPlayer Interface" << std::endl;
            return nullptr;
        }
    }
};
#endif