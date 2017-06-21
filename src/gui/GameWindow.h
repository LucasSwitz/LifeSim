#ifndef GAMEGUI_H
#define GAMEGUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Color.hpp>
#include <queue>

class GameWindow
{

void Update();
void Draw(const sf::Drawable drawable);
void Clear();

private:
    sf::RenderWindow _main_window;
    std::queue<sf::Drawable> _drawables_queue;
};


#endif