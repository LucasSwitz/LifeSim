#ifndef ACTION_H
#define ACTION_H

#include <unordered_map>

class Actor;

class Action
{
    friend class ActionFactory;
public:
    virtual void Start() = 0;
    virtual void Perform() = 0;
    virtual bool IsFinished() = 0;
    std::string _name;

protected:
    virtual Action* BuildFromScript(std::unordered_map<std::string, std::string> flags) = 0;

    Action(std::string name = "unnamed"): _name(name){};
    Actor* _performer;

};

#endif