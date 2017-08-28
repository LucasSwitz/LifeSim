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
    private:
        static MessageDispatch* _instance;
};
#endif