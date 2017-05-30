#include "Nutrition.h"

void Nutrition::Check(&Actor actor)
{
    if(actor.getHunger() <= 0)
    {
        actor.health--;
    }
}