#ifndef GAMEGUI_H
#define GAMEGUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <queue>
#include "src/gui/gui_tools/DevelopmentOverlay.h"

class GameWindow
{

  public:
    GameWindow();
    void Update(float time_elapsed);
    void Draw(const sf::Drawable *drawable);
    void Init();
    void Clear();

  private:
    sf::RenderWindow _main_window;
    //std::queue<sf::Drawable> _drawables_queue;
    void PollEvents();
};

#endif