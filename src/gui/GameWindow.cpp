#include "GameWindow.h"


GameWindow::GameWindow() : _main_window(sf::VideoMode(200, 200), "SFML works!", sf::Style::Fullscreen)
{

}

GameWindow::Draw(const sf::Drawable& drawable)
{
    _drawables_queue.push(drawable);
}

GameWindow::Update()
{
    _main_window->clear(sf::Color::White);

    for(auto it = _drawables_queue.begin(); it != _drawables.end(); i++)
    {
        _main_window->draw(*it);
    }

    _main_window->display();
}