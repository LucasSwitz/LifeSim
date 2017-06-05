#ifndef APPLE_H
#define APPLE_H

#include "src/game_objects/Entity.h"


class Apple : public Entity
{
public:
    Apple()
    {
        AddAttribute("Nutrition",5);
    }
};

#endif