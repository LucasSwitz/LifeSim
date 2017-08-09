#ifndef PMIDGWINDOW_H
#define PMIDGWINDOW_H

#include <queue>
#include <unordered_map>
#include <list>
#include <climits>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "src/event/EngineEventManager.h"
#include "src/event/EventType.h"
#include "src/graphics/gui/TextureCache.h"
#include "src/graphics/gui/SFMLWindowListener.h"
#include "src/component/ComponentUser.h"

#include "src/utils/logging/Logging.h"

#include "src/event/EventSubscriber.h"
#include "src/event/EventType.h"

#include "src/graphics/gui/rendering/GraphicsPreprocessor.h"

class PMIDGWindow : public EventSubscriber
{
  public:
    struct LayeredGraphic
    {
        LayeredGraphic(sf::Drawable *draw, int lay) : drawable(draw), layer(lay){};
        ~LayeredGraphic()
        {
            delete drawable;
        }
        int layer = 0;
        sf::Drawable *drawable;
    };

    PMIDGWindow() : _window(sf::VideoMode(1200, 1200), "PMIDG")
    {
        EngineEventManager::Instance()->RegisterSubscriber(this);
    }

    sf::RenderWindow &SFWindow()
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
            sf::Drawable *to_draw = _drawables_queue.top()->drawable;
            _window.draw(*to_draw);
            _drawables_queue.pop();
            delete to_draw;
        }
    }

    void Display()
    {
        _window.display();
    }

    void Draw(sf::Drawable *drawable)
    {
        LayeredGraphic *lg = new LayeredGraphic(drawable, INT_MAX);
    }

    void Draw(LayeredGraphic *lg)
    {
        _drawables_queue.push(lg);
    }

    void DrawNow(sf::Drawable &drawable)
    {
        _window.draw(drawable);
    }

    void DrawComponentUser(ComponentUser *user)
    {
        if (!user->HasComponent("Position") || !user->HasComponent("Graphics"))
        {
            LOG->LogFile("Attempted to Draw Component User with Invalid Components");
            return;
        }

        std::string sprite_path = user->GetComponentValueString("Graphics", "sprite");
        int layer = user->GetComponentValueFloat("Graphics", "layer");
        sf::Texture *texture = nullptr;

        if (texture = _texture_cache.GetTexture(sprite_path))
        {
            sf::Sprite *sprite = new sf::Sprite();
            _preprocesser.ProcessComponentUser(user, texture, sprite);

            LayeredGraphic* lg = new LayeredGraphic(sprite, layer);
            Draw(lg);
        }
        else
        {
            LOG->LogFile("Invalid Sprite File: " + sprite_path);
        }
    }

    TextureCache &GetTextureCache()
    {
        return _texture_cache;
    }

    void Shutdown()
    {
        _window.close();
    }

    void OnEvent(Event &e)
    {
        if (e.id == EventType::DRAW_REQUEST_EVENT)
        {
            ComponentUser *user = e.InfoToType<ComponentUser *>();
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
            EngineEventManager::Instance()->LaunchEvent(new_event);
        }
        else if (e.type == sf::Event::KeyPressed)
        {
            if (e.key.code == sf::Keyboard::W)
            {
                Event new_event(EventType::W_DOWN_EVENT, -1, -1);
                EngineEventManager::Instance()->LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::A)
            {
                Event new_event(EventType::A_DOWN_EVENT, -1, -1);
                EngineEventManager::Instance()->LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::S)
            {
                Event new_event(EventType::S_DOWN_EVENT, -1, -1);
                EngineEventManager::Instance()->LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::D)
            {
                Event new_event(EventType::D_DOWN_EVENT, -1, -1);
                EngineEventManager::Instance()->LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::E)
            {
                Event new_event(EventType::E_DOWN_EVENT, -1, -1);
                EngineEventManager::Instance()->LaunchEvent(new_event);
            }
        }
        else if (e.type == sf::Event::KeyReleased)
        {
            if (e.key.code == sf::Keyboard::W)
            {
                Event new_event(EventType::W_UP_EVENT, -1, -1);
                EngineEventManager::Instance()->LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::A)
            {
                Event new_event(EventType::A_UP_EVENT, -1, -1);
                EngineEventManager::Instance()->LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::S)
            {
                Event new_event(EventType::S_UP_EVENT, -1, -1);
                EngineEventManager::Instance()->LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::D)
            {
                Event new_event(EventType::D_UP_EVENT, -1, -1);
                EngineEventManager::Instance()->LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::E)
            {
                Event new_event(EventType::E_UP_EVENT, -1, -1);
                EngineEventManager::Instance()->LaunchEvent(new_event);
            }
        }
        for (SFMLWindowListener *listener : _window_listeners)
        {
            if (listener->OnWindowEvent(e))
                break;
        }
    }

    void AddWindowListener(SFMLWindowListener *listener)
    {
        _window_listeners.push_back(listener);
    }

  protected:
    sf::RenderWindow _window;

  private:
    class GraphicsComparator
    {
      public:
        bool operator()(LayeredGraphic *g1, LayeredGraphic *g2)
        {
            return g1->layer > g2->layer;
        }
    };

    TextureCache _texture_cache;
    std::priority_queue<LayeredGraphic *, std::vector<LayeredGraphic *>, GraphicsComparator> _drawables_queue;
    std::list<SFMLWindowListener *> _window_listeners;
    GraphicsPreprocessor _preprocesser;
};

#endif