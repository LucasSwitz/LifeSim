#include "Nutrition.h"

void Nutrition::Check(Actor& actor)
{
    if(actor.GetHunger() <= 10)
    {
        actor.ApplyCondition("Starved");
    }
}