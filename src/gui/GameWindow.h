#ifndef GAMEGUI_H
#define GAMEGUI_H

#include <queue>
#include <unordered_map>
#include "src/gui/gui_tools/DevelopmentOverlay.h"
#include "src/component/ComponentUser.h"
#include "src/utils/logging/Logging.h"
#include "src/event/EventManager.h"
#include "src/event/EventType.h"

class GameWindow
{

  public:
    GameWindow();
    void Update(float time_elapsed);
    void Draw(sf::Drawable *drawable);
    void DrawFromComponents(const ComponentUser* user);
    void Init();
    void Clear();
    void Shutdown();
    static GameWindow* instance;
    static int window_count;

    static GameWindow* Instance()
    {
      if(!instance)
      {
        return NewInstance();
      }

      return instance;
    }

    static GameWindow* NewInstance()
    {
        window_count++;
        instance = new GameWindow();
        return instance;
    }

  private:
    void PollEvents();
    void HandleEvent(sf::Event& event);

    sf::RenderWindow _main_window;
    std::queue<sf::Drawable*> _drawables_queue;
    TextureCache _texture_cache;

};

#endif