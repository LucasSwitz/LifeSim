#ifndef GOAL_H
#define GOAL_H

#include <string>
#include <vector>
#include <iostream>

class GoalBase;
class Actor;

class Goal{
    
public:
    virtual int Priority(Actor& actor) = 0;
    virtual void Start(Actor& actor) = 0;
    virtual bool isFulfilled(Actor& actor) = 0;
    virtual void Finish(Actor& actor) {};
    virtual void Check(Actor& t) = 0;

    const std::string _name;
    Goal(std::string name) : _name(name){};
    void AddActionScript(std::string script)
    {
        _actions.push_back(script);
    };

protected:

    std::vector<std::string> _actions;
};
#endif