#ifndef ACTIONEAT_H
#define ACTIONEAT_H

#include "src/game_objects/Entity.h"
#include "src/game_objects/actor/actions/Action.h"
#include "src/game_objects/EntityManager.h"

class ActionEat : public Action
{
  public:
    ActionEat() : Action("Eat"){};
    void Start() override;
    void Perform() override;
    bool IsFinished() override;

  protected:
    Action* BuildFromScript(std::unordered_map<std::string, std::string> flags) override;

  private:
    Entity* _target = nullptr;
    bool _isFinished = false;
};

#endif