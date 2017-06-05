#include "Nutrition.h"

void Nutrition::Start(Actor& actor)
{
    
}

void Nutrition::Check(Actor& actor)
{
    if(actor.GetInternalValue("Hunger") <= 10)
    {
        //make actor eat food
        actor.AddToActionQueue(new ActionChain(_actions, actor));

        //appy starved condition
        actor.ApplyCondition("Starved");
    }
}

void Nutrition::Finish(Actor& actor)
{

}

bool Nutrition::isFulfilled(Actor& actor)
{
    return false;
}

int Nutrition::Priority(Actor& actor)
{
    return 0;
}

