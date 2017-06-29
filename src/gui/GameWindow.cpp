#include "GameWindow.h"


GameWindow::GameWindow() : _main_window(sf::VideoMode(600, 600), "SFML works!")
{
    
}

void GameWindow::Init()
{
     DevelopmentOverlay::Instance()->Init(_main_window);
}

void GameWindow::Draw(const sf::Drawable* drawable)
{
   //_drawables_queue.push(drawable);
}

void GameWindow::Update(float time_elapsed)
{
    PollEvents();
    _main_window.clear(sf::Color::White);
    
    sf::Time t = sf::seconds(time_elapsed);
    DevelopmentOverlay::Instance()->Draw(_main_window, t);

    /*for(auto it = _drawables_queue.begin(); it != _drawables.end(); i++)
    {
        _main_window->draw(*it);
    }*/

    _main_window.display();
}

void GameWindow::PollEvents()
{
        sf::Event event;
        while (_main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _main_window.close();
        }
}