#include "Need.h"
#include "Actor.h"

class Nutrition : public Need
{
public:
    void Check(&Actor actor) override;
    virtual int Priority(Actor& actor) const{return 0;}
    virtual bool isFulfilled(Actor& actor) const{return false;}
    virtual void Finish(Actor& actor) const {return false;};
    
    Nutrition* Instance(){
        static Nutrition instance;
        return &instance;
    };
}