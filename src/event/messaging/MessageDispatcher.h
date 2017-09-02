#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H

#include "src/event/messaging/MessageDispatch.h"

class MessageDispatcher
{
public:
    virtual void AssignToDispatch(MessageDispatch* dispatch)
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

    MessageDispatch* GetAssignedDispatch()
    {
        return _dispatch;
    }

    bool IsAssignedToDispatch()
    {
        return _dispatch != nullptr;
    }

private:
    MessageDispatch* _dispatch;

};
#endif