#ifndef NUTRITION_H
#define NUTRITION_H

#include <queue>
#include "src/game_objects/actor/goal/Goal.h"
#include "src/game_objects/actor/actions/ActionChain.h"
#include "src/game_objects/actor/Actor.h"

class Actor;

class Nutrition : public Goal
{
public:
    void Check(Actor& actor) override;
    virtual int Priority(Actor& actor);
    virtual bool isFulfilled(Actor& actor);
    virtual void Finish(Actor& actor);
    virtual void Start(Actor& actor) override;
    
    static Nutrition* Instance(){
        static Nutrition instance;
        return &instance;
    };
    
protected:
     Nutrition();
private:
   
};

#endif