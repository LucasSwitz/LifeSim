#ifndef DEVELOPMENTOVERLAY_H
#define DEVELOPMENTOVERLAY_H


#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "src/gui/gui_tools/Log.h"

class DevelopmentOverlay
{
    public:
        void Draw(sf::RenderWindow& render_window,  sf::Time &deltaTime);
        void Init(sf::RenderWindow& render_window);
        void Shutdown();
        Log& GetLog();

        static DevelopmentOverlay* Instance()
        {
            static DevelopmentOverlay instance;
            return &instance;
        }
    private:
        DevelopmentOverlay();
        Log _log;

};
#endif