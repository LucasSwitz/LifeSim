#ifndef TBArcadeController_H
#define TBArcadeController_H

#include "TBArcadeControllerService.h"

class TBArcadeController
{
  public:
    TBArcadeController(int id){
        _controller_service.Start();
    };

    int YAxis()
    {
        _controller_service.Get().y_axis;
    }

    int XAxis()
    {
        _controller_service.Get().x_axis;
    }

    bool LeftButton()
    {
        return _controller_service.Get().button_left;
    }

    bool RightButton()
    {
        return _controller_service.Get().button_right;
    }

  private:
    TBArcadeControllerService _controller_service;
};
#endif