#ifndef ACTION_H
#define ACTION_H

#include <unordered_map>

class Actor;
class ActionScriptFactory;

class ActionScript
{
    friend class ActionScriptFactory;
public:
    void Start()
    {

    };

    void Perform()
    {

    };

    bool IsFinished()
    {


    };

protected:
    Action(std::string script_name) : _script_name(name)
    {

    };
    
    std::string _script_name;
    Actor* _performer;
};

#endif