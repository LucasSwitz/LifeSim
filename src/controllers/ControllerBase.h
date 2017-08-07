#ifndef CONTROLLERBASE_H
#define CONTROLLERBASE_H

class ControllerBase
{
  public:
    void Add(PlayerController *controller)
    {
        if (IDAvailable(controller->ID()))
            _controllers.insert(std::make_pair(controller->ID(), controller));
    }
    PlayerController* Get(int id)
    {
        if (!IDAvailable(id))
            return _controllers.at(id);
        return nullptr;
    }

    bool IDAvailable(int id)
    {
        return _controllers.find(id) != _controllers.end();
    }

  private:
    std::map<int, PlayerController *> _controllers;
};
#endif