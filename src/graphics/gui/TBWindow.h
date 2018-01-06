#ifndef TBWINDOW_H
#define TBWINDOW_H

#include <queue>
#include <unordered_map>
#include <list>
#include <climits>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "src/event/EventType.h"
#include "src/graphics/gui/TextureCache.h"
#include "src/graphics/gui/SFMLWindowListener.h"
#include "src/component/ComponentUser.h"

#include "src/utils/logging/Logging.h"

#include "src/event/EventSubscriber.h"
#include "src/event/EventType.h"
#include "src/event/EventManager.h"

#include "src/graphics/gui/rendering/GraphicsPreprocessor.h"

#include "src/game/EngineGlobals.h"

class TBWindow : public EventSubscriber
{
  public:
    struct LayeredGraphic
    {
        LayeredGraphic(ptr<sf::Drawable> draw, ptr<sf::Texture> texture, int lay) : drawable(draw), layer(lay){};
        ~LayeredGraphic(){}
        int layer = 0;
        ptr<sf::Drawable> drawable = nullptr;
        ptr<sf::Texture> texture = nullptr;
    };

    TBWindow(EventManager& program_event_manager,EventManager& engine_event_manager) : 
        _program_event_manager(program_event_manager), _engine_event_manager(engine_event_manager), _window(sf::VideoMode(1200, 1200), "TB")
    {
        _id = last_id;
        _engine_event_manager.RegisterSubscriber(this);
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
            ptr<LayeredGraphic> to_draw = _drawables_queue.top();
            _window.draw(*(to_draw->drawable));
            _drawables_queue.pop();
        }
    }

    void Display()
    {
        _window.display();
    }

    void Focus()
    {
        EngineGlobals::TargetWindow = _id;
    }

    void Draw(ptr<sf::Drawable> drawable)
    {
        ptr<LayeredGraphic> lg(new LayeredGraphic(drawable, nullptr, INT_MAX));
        Draw(lg);
    }

    void Draw(ptr<LayeredGraphic> lg)
    {
        _drawables_queue.push(lg);
    }

    void DrawNow(sf::Drawable &drawable)
    {
        _window.draw(drawable);
    }

    void DrawComponentUser(ComponentUser* user)
    {
        if (!user->HasComponent("Position") || !user->HasComponent("Graphics"))
        {
            LOG->LogFile("Attempted to Draw Component User with Invalid Components");
            return;
        }

        std::string sprite_path = user->GetComponentValueString("Graphics", "sprite");
        int layer = user->GetComponentValueFloat("Graphics", "layer");

        ptr<sf::Texture> texture = nullptr;

        if (texture = _texture_cache.GetTexture(sprite_path))
        {
            ptr<sf::Sprite> sprite (new sf::Sprite());
            _preprocesser.ProcessComponentUser(user, texture, sprite);

            ptr<LayeredGraphic> lg(new LayeredGraphic(sprite, texture, layer));
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
        _engine_event_manager.Deregister(this);
        _window.close();
    }

    void OnEvent(Event &e)
    {
        if (e.id == EventType::DRAW_REQUEST_EVENT && e.target_id == _id)
        {
            ComponentUser* user =  (e.InfoToType<ComponentUser *>());
            DrawComponentUser(user);
        }
        else if (e.id == EventType::RECENTER_VIEW_EVENT && e.target_id == _id)
        {
            std::vector<float> *center_coords =
                e.InfoToType<std::vector<float> *>();
            SetViewCenter((*center_coords)[0], (*center_coords)[1]);
            delete center_coords;
        }
    }

    std::list<Subscription> GetSubscriptions() override
    {
        std::list<Subscription> subs = {Subscription(EventType::DRAW_REQUEST_EVENT, {_id}),
                                        Subscription(EventType::RECENTER_VIEW_EVENT, {_id})};
        return subs;
    }

    void HandleEvent(sf::Event &e)
    {
        if (e.type == sf::Event::Closed)
        {
            Event new_event(EventType::CLOSE_WINDOW_EVENT, _id, -1);
            _program_event_manager.LaunchEvent(new_event);
        }
        else if (e.type == sf::Event::KeyPressed)
        {
            if (e.key.code == sf::Keyboard::W)
            {
                Event new_event(EventType::W_DOWN_EVENT, -1, -1);
                _program_event_manager.LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::A)
            {
                Event new_event(EventType::A_DOWN_EVENT, -1, -1);
                _program_event_manager.LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::S)
            {
                Event new_event(EventType::S_DOWN_EVENT, -1, -1);
                _program_event_manager.LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::D)
            {
                Event new_event(EventType::D_DOWN_EVENT, -1, -1);
                _program_event_manager.LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::E)
            {
                Event new_event(EventType::E_DOWN_EVENT, -1, -1);
                _program_event_manager.LaunchEvent(new_event);
            }
        }
        else if (e.type == sf::Event::KeyReleased)
        {
            if (e.key.code == sf::Keyboard::W)
            {
                Event new_event(EventType::W_UP_EVENT, -1, -1);
                _program_event_manager.LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::A)
            {
                Event new_event(EventType::A_UP_EVENT, -1, -1);
                _program_event_manager.LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::S)
            {
                Event new_event(EventType::S_UP_EVENT, -1, -1);
                _program_event_manager.LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::D)
            {
                Event new_event(EventType::D_UP_EVENT, -1, -1);
                _program_event_manager.LaunchEvent(new_event);
            }
            else if (e.key.code == sf::Keyboard::E)
            {
                Event new_event(EventType::E_UP_EVENT, -1, -1);
                _program_event_manager.LaunchEvent(new_event);
            }
        }
        for (SFMLWindowListener* listener : _window_listeners)
        {
            if (listener->OnWindowEvent(e))
                break;
        }
    }

    void AddWindowListener(SFMLWindowListener* listener)
    {
        _window_listeners.push_back(listener);
    }

    int ID()
    {
        return _id;
    }

    ~TBWindow()
    {
        
    }

    void SetViewCenter(float x, float y)
    {
        sf::View view = _window.getView();
        view.setCenter(x, y);
        _window.setView(view);
    }

    void SetName(std::string name)
    {
        _window.setTitle(name);
    }

  protected:
    sf::RenderWindow _window;

  private:
    class GraphicsComparator
    {
      public:
        bool operator()(ptr<LayeredGraphic> g1, ptr<LayeredGraphic> g2)
        {
            return g1->layer > g2->layer;
        }
    };

    TextureCache _texture_cache;
    std::priority_queue<ptr<LayeredGraphic>, std::vector<ptr<LayeredGraphic>>, GraphicsComparator> _drawables_queue;
    std::list<SFMLWindowListener*> _window_listeners;
    GraphicsPreprocessor _preprocesser;
    EventManager& _program_event_manager;
    EventManager& _engine_event_manager;
    int _id;
    static int last_id;
};

#endif