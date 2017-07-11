#ifndef PMIDGWINDOW_H
#define PMIDGWINDOW_H

#include <queue>
#include <unordered_map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "src/event/EventManager.h"
#include "src/event/EventType.h"
#include "src/game/gui/TextureCache.h"
#include "src/component/ComponentUser.h"

#include "src/utils/logging/Logging.h"

#include "src/event/EventSubscriber.h"
#include "src/event/EventType.h"

class PMIDGWindow : public EventSubscriber
{
  public:
    PMIDGWindow() : _window(sf::VideoMode(600, 600), "HELLO!")
    {
        EventManager::Instance()->RegisterSubscriber(this);
    }

    sf::RenderWindow& SFWindow()
    {
        return _window;
    }

    void PollEvents()
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            HandleEvent(event);
        }
    }


    void Clear()
    {
        _window.clear(sf::Color::White);
    }

    void Render()
    {

        while (!_drawables_queue.empty())
        {
            sf::Drawable *to_draw = _drawables_queue.front();
            _window.draw(*to_draw);
            _drawables_queue.pop();
        }
    }

    void Display()
    {
        _window.display();
    }

    void Draw(sf::Drawable *drawable)
    {
        _drawables_queue.push(drawable);
    }

    void DrawComponentUser(ComponentUser *user)
    {
        if (!user->HasComponent("Position") || !user->HasComponent("Graphics"))
        {
            LOG->LogFile("Attempted to Draw Component User with Invalid Components");
            return;
        }

        std::string sprite_path = user->GetComponentValueString("Graphics", "sprite");

        sf::Texture *texture = nullptr;
        if (texture = _texture_cache.GetTexture(sprite_path))
        {
            sf::Sprite *sprite = new sf::Sprite();
            sprite->setTexture(*texture);
            sprite->setPosition(user->GetComponentValueFloat("Position", "x"), user->GetComponentValueFloat("Position", "y"));
            Draw(sprite);
        }
        else
        {
            LOG->LogFile("Invalid Sprite File: " + sprite_path);
        }
    }

    TextureCache& GetTextureCache()
    {
        return _texture_cache;
    }

    void Shutdown()
    {
        _window.close();
    }

    void OnEvent(Event& e)
    {
        if(e.id == EventType::DRAW_REQUEST_EVENT)
        {
            std::cout << "Draw Request!" << std::endl;
            ComponentUser* user = e.DereferenceInfoToType<ComponentUser*>();
            DrawComponentUser(user);
        }
    }

    std::list<Subscription> GetSubscriptions() override
    {
        std::list<Subscription> subs = {Subscription(EventType::DRAW_REQUEST_EVENT)};
        return subs;
    }

    void HandleEvent(sf::Event &e)
    {
        if (e.type == sf::Event::Closed)
        {
            Event new_event(EventType::CLOSE_GAME_WINDOW_EVENT, -1, -1);
            EventManager::Instance()->LaunchEvent(new_event);
        }
        else if (e.type == sf::Event::KeyPressed)
        {
            if (e.key.code == sf::Keyboard::W)
            {
                Event new_event(EventType::W_DOWN_EVENT, -1, -1);
                EventManager::Instance()->LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::A)
            {
                Event new_event(EventType::A_DOWN_EVENT, -1, -1);
                EventManager::Instance()->LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::S)
            {
                Event new_event(EventType::S_DOWN_EVENT, -1, -1);
                EventManager::Instance()->LaunchEvent(new_event);
            }
        }
        else if (e.type == sf::Event::KeyReleased)
        {
            if (e.key.code == sf::Keyboard::W)
            {
                Event new_event(EventType::W_UP_EVENT, -1, -1);
                EventManager::Instance()->LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::A)
            {
                Event new_event(EventType::A_UP_EVENT, -1, -1);
                EventManager::Instance()->LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::S)
            {
                Event new_event(EventType::S_UP_EVENT, -1, -1);
                EventManager::Instance()->LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::D)
            {
                Event new_event(EventType::D_UP_EVENT, -1, -1);
                EventManager::Instance()->LaunchEvent(new_event);
            }
        }
    }

  private:
    sf::RenderWindow _window;
    TextureCache _texture_cache;
    std::queue<sf::Drawable*> _drawables_queue;

};

#endif