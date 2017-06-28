#ifndef DEVELOPMENTOVERLAY_H
#define DEVELOPMENTOVERLAY_H


#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class DevelopmentOverlay
{
    public:
        void Draw();
        void Init(sf::RenderWindow& render_window)
        void Shutdown();
    private:

};
#endif