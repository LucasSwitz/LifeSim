#ifndef SIDESCROLLERPLAYERINTERFACE_H
#define SIDESCROLLERPLAYERINTERFACE_H

class SideScrollerPlayerInterface 
{
    public:
    SideScrollerPlayerInterface(){};

    virtual bool Jump() = 0; 
    virtual bool Left() = 0; 
    virtual bool Right() = 0; 
    virtual bool Action() = 0; 
};
#endif