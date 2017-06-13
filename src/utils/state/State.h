#ifndef STATE_H
#define STATE_H

template<typename T>
class State
{
public:
    virtual void Enter(T& t) = 0;    
    virtual void Execute(T& t) = 0;
    virtual void Exit(T& t) = 0;
};

#endif