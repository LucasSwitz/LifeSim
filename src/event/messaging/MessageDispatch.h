#ifndef MESSAGEDISPATCH_H
#define MESSAGEDISPATCH_H

#include "src/event/EventManager.h"

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