#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include "src/controller/KeyboardSideScollerPlayerController.h"

class ControllerFactory
{
    public:
        static GetController(const int type, const int id)
        {
            switch(type)
            {
                case 0:
                    return new KeyboardSideScollerPlayerController(id);

                default:
                    std::cout << "Unknown Controller Type: " << type << std::endl;
            }
        }
}