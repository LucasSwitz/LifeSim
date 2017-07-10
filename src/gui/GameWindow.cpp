#include "GameWindow.h"

GameWindow* GameWindow::instance = nullptr;
int GameWindow::window_count = 0;

GameWindow::GameWindow() : _main_window(sf::VideoMode(600, 600), std::to_string(window_count))
{

}

void GameWindow::Init()
{
     DevelopmentOverlay::Instance()->Init(_main_window, _texture_cache);
}

void GameWindow::Draw(sf::Drawable* drawable)
{
   _drawables_queue.push(drawable);
}

//users must have a position and a graphic component
void GameWindow::DrawFromComponents(const ComponentUser* user)
{
    if(!user->HasComponent("Position") || !user->HasComponent("Graphics"))
    {
        LOG->LogFile("Attempted to Draw Component User with Invalid Components");
        return;
    }

    std::string sprite_path = user->GetComponentValueString("Graphics","sprite");

    sf::Texture * texture = nullptr;
    if(texture = _texture_cache.GetTexture(sprite_path))
    {
        sf::Sprite* sprite = new sf::Sprite();
        sprite->setTexture(*texture);
        sprite->setPosition(user->GetComponentValueFloat("Position","x"),user->GetComponentValueFloat("Position","y"));
        Draw(sprite);
    }
    else
    {
        LOG->LogFile("Invalid Sprite File: " + sprite_path);
    }
}

void GameWindow::Update(float time_elapsed)
{
    PollEvents();
    _main_window.clear(sf::Color::White);
    
    sf::Time t = sf::seconds(time_elapsed);

    DevelopmentOverlay::Instance()->Draw(_main_window, t);

    while(!_drawables_queue.empty())
    {   
        sf::Drawable* to_draw = _drawables_queue.front();
        _main_window.draw(*to_draw);
        _drawables_queue.pop();
    }

    _main_window.display();
}

void GameWindow::Shutdown()
{
    _main_window.close();
}

void GameWindow::PollEvents()
{
        sf::Event event;
        while (_main_window.pollEvent(event))
        {
            HandleEvent(event);
        }
}

void GameWindow::HandleEvent(sf::Event& e)
{
    if (e.type == sf::Event::Closed)
    {
        Event new_event(EventType::CLOSE_GAME_WINDOW_EVENT,-1,-1);
        EventManager::Instance()->LaunchEvent(new_event);
    }
    else if(e.type == sf::Event::KeyPressed)
    {
        if(e.key.code == sf::Keyboard::W)
        {
            Event new_event(EventType::W_DOWN_EVENT,-1,-1);
            EventManager::Instance()->LaunchEvent(new_event);
        }
        else if(e.key.code == sf::Keyboard::A)
        {
            Event new_event(EventType::A_DOWN_EVENT,-1,-1);
            EventManager::Instance()->LaunchEvent(new_event);
        }
        else if(e.key.code == sf::Keyboard::S)
        {
            Event new_event(EventType::S_DOWN_EVENT,-1,-1);
            EventManager::Instance()->LaunchEvent(new_event);
        }
        else if(e.key.code == sf::Keyboard::D)
        {
            Event new_event(EventType::D_DOWN_EVENT,-1,-1);
            EventManager::Instance()->LaunchEvent(new_event);
        }

    }
    else if(e.type == sf::Event::KeyReleased)
    {
        if(e.key.code == sf::Keyboard::W)
        {
            Event new_event(EventType::W_UP_EVENT,-1,-1);
            EventManager::Instance()->LaunchEvent(new_event);
        }
        else if(e.key.code == sf::Keyboard::A)
        {
            Event new_event(EventType::A_UP_EVENT,-1,-1);
            EventManager::Instance()->LaunchEvent(new_event);
        }
        else if(e.key.code == sf::Keyboard::S)
        {
            Event new_event(EventType::S_UP_EVENT,-1,-1);
            EventManager::Instance()->LaunchEvent(new_event);
        }
        else if(e.key.code == sf::Keyboard::D)
        {
            Event new_event(EventType::D_UP_EVENT,-1,-1);
            EventManager::Instance()->LaunchEvent(new_event);
        }

    }
}