#ifndef KEYBOARDPLAYERCONTROLLER_H
#define KEYBOARDPLAYERCONTROLLER_H

#include "src/controllers/KeyboardController.h"
#include "src/controllers/SideScrollerPlayerInterface.h"

class KeyboardSideScrollerPlayerController : public KeyboardController, public SideScrollerPlayerInterface
{
  public:
    KeyboardSideScrollerPlayerController(int id) : KeyboardController(id) {
        
    }

    virtual bool Jump()
    {
        return Get(W_KEY_TRIGGER);
    }

    virtual bool Left()
    {
        return Get(A_KEY_TRIGGER);
    }

    virtual bool Right()
    {
        return Get(D_KEY_TRIGGER);
    }

    virtual bool Action()
    {
        return Get(E_KEY_TRIGGER);
    }

    static KeyboardController* Downcast(Controller* controller)
    {
        KeyboardController* keyboard_controller = dynamic_cast<KeyboardController*>(controller);

        if(keyboard_controller)
            return keyboard_controller;

        return nullptr;
    }
};
#endif