#ifndef NUTRITION_H
#define NUTRITION_H

#include "src/game_objects/actor/Actor.h"
#include "src/game_objects/actor/Goal.h"

class Nutrition : public Goal
{
public:
    void Check(Actor& actor) override;
    virtual int Priority(Actor& actor) const{return 0;}
    virtual bool isFulfilled(Actor& actor) const{return false;}
    virtual void Finish(Actor& actor) const {};
    
    static Nutrition* Instance(){
        static Nutrition instance;
        return &instance;
    };

private:
    Nutrition() : Goal("Nutrition"){};
    
};

#endif