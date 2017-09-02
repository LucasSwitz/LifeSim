#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include "src/controllers/KeyboardSideScrollerPlayerController.h"

class ControllerFactory
{
    public:
        static Controller* GetController(const int type, const int id)
        {
            switch(type)
            {
                case 0:
                    return new KeyboardSideScrollerPlayerController(id);
                default:
                    std::cout << "Unknown Controller Type: " << type << std::endl;
                    return nullptr;
            }
        }
};

#endif