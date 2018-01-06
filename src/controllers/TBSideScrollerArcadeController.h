#ifndef TBSideScrollerArcadeController_H
#define TBSideScrollerArcadeController_H

#include "src/controllers/TBArcadeController.h"
#include "SideScrollerPlayerInterface.h"

class TBSideScrollerArcadeController : public SideScrollerPlayerInterface, public TBArcadeController
{
  public:

    TBSideScrollerArcadeController(int id) : TBArcadeController(id), SideScrollerPlayerInterface(id){}

    bool Jump()
    {
        return LeftButton();
    }

    bool Left()
    {
        return (XAxis() < 0);
    }

    bool Right()
    {
        return (XAxis() > 0);
    }

    bool Action()
    {
        return RightButton();
    }
};

#endif