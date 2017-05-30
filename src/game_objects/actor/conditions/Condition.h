#ifndef CONDITION_H
#define CONDITION_H
template <typename T>
class Condition
{
    void virtual Start(T& t) = 0;
    void virtual Update(T& t) = 0;
    void virtual End(T& t) = 0;
    bool virtual isFinished(T& t) = 0;
};
#endif