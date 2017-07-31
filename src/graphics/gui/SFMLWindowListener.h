#ifndef SFMLWINDOWLISTNER_H
#define SFMLWINDOWLISTNER_H

#include <SFML/Window/Event.hpp>

class SFMLWindowListener
{
    public:
        virtual bool OnWindowEvent(sf::Event& e) = 0;
};
#endif