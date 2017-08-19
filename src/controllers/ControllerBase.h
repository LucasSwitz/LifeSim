#ifndef CONTROLLERBASE_H
#define CONTROLLERBASE_H

#include "src/controllers/Controller.h"

class ControllerBase
{
  public:
    static void AddController(Controller* controller)
    {
        Instance()->Add(controller);
    }

    static Controller* GetController(int id)
    {
        return Instance()->Get(id);
    }

    static ControllerBase* Instance()
    {
        static ControllerBase instance;
        return &instance;
    }

    bool HasControllerWithID(int id)
    {
        return !IDAvailable(id);
    }

    std::map<int, Controller *>& GetAll()
    {
        return _controllers;
    }

  private:
    void Add(Controller *controller)
    {
        if (IDAvailable(controller->ID()))
        {
            _controllers.insert(std::make_pair(controller->ID(), controller));
            std::cout << "Controller Added: " << controller->ID() << std::endl; 
        }
    }

    Controller* Get(int id)
    {
        if (HasControllerWithID(id))
            return _controllers.at(id);
        return nullptr;
    }

    bool IDAvailable(int id)
    {
        return _controllers.find(id) == _controllers.end();
    }

    std::map<int, Controller *> _controllers;
};
#endif