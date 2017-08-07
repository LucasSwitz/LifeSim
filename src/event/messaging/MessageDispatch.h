#ifndef MESSAGEDISPATCH_H
#define MESSAGEDISPATCH_H

#include "src/event/EventManager.h"

/**
    Purpose: MessageDispatch is an EventManager implementation that can have its 
            global instance be swapped. This is utilized by GameState to handle
            game-related communications.
**/
class MessageDispatch : public EventManager
{
    public:
        static void GiveOwnership(MessageDispatch* dispatch)
        {
            _instance = dispatch;
        }

        static MessageDispatch* Instance()
        {
            return _instance;
        }

    private:
        static MessageDispatch* _instance;
};
#endif