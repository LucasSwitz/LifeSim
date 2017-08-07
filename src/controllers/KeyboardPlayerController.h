#ifndef KEYBOARDPLAYERCONTROLLER_H
#define KEYBOARDPLAYERCONTROLLER_H

class KeyboardPlayerController : public Keyboard, public PlayerController
{
  public:
    KeyboardPlayerController(int id) : PlayerController(id) {}

    virtual bool Jump()
    {
        return Get("W");
    }

    virtual bool Left()
    {
        return Get("A");
    }

    virtual bool Right()
    {
        return Get("D");
    }

    virtual bool Action()
    {
        return Get("E");
    }
};
#endif