#ifndef KEYBOARDPLAYERCONTROLLER_H
#define KEYBOARDPLAYERCONTROLLER_H

#include "src/controllers/Keyboard.h"
#include "src/controllers/SideScrollerPlayerInterface.h"



class KeyboardSideScrollerPlayerController : public Keyboard, public SideScrollerPlayerInterface
{
  public:
    static int W_KEY_TRIGGER;
    static int A_KEY_TRIGGER;
    static int S_KEY_TRIGGER;
    static int D_KEY_TRIGGER;
    static int E_KEY_TRIGGER;

    KeyboardSideScrollerPlayerController(int id, EventManager& ev) : SideScrollerPlayerInterface(id), Keyboard(ev) {
        
    }

    void Poll(){
        Set(W_KEY_TRIGGER,GetKey('W'));
        Set(A_KEY_TRIGGER,GetKey('A'));
        Set(S_KEY_TRIGGER,GetKey('S'));
        Set(D_KEY_TRIGGER,GetKey('D'));
        Set(E_KEY_TRIGGER,GetKey('E'));
    };

    bool Jump()
    {
        return Get(W_KEY_TRIGGER);
    }

    bool Left()
    {
        return Get(A_KEY_TRIGGER);
    }

    bool Right()
    {
        return Get(D_KEY_TRIGGER);
    }

    bool Action()
    {
        return Get(E_KEY_TRIGGER);
    }
};
#endif