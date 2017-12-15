#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H

#include "src/event/EventManager.h"

class MessageDispatcher
{
public:
    virtual void AssignToDispatch(EventManager* dispatch)
    {
        _dispatch = dispatch;
    }

    void DispatchMessage(Event& e)
    {
        if(_dispatch)
            _dispatch->LaunchEvent(e);
        else 
            std::cout << "Dispatch not assigned!" << std::endl;
    }

    EventManager* GetAssignedDispatch()
    {
        return _dispatch;
    }

    bool IsAssignedToDispatch()
    {
        return _dispatch != nullptr;
    }

private:
    EventManager* _dispatch;

};
#endif