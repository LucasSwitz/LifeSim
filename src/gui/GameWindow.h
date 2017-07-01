#ifndef GAMEGUI_H
#define GAMEGUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <queue>
#include <unordered_map>
#include "src/gui/gui_tools/DevelopmentOverlay.h"
#include "src/component/ComponentUser.h"
#include "src/utils/logging/Logging.h"

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
        instance = new GameWindow();
        return instance;
    }

  private:

    sf::Texture* GetTexture(std::string name);
    bool TextureCached(std::string name);
    bool LoadTexture(std::string name);
    sf::RenderWindow _main_window;
    std::queue<sf::Drawable*> _drawables_queue;
    std::unordered_map<std::string, sf::Texture*> _texture_cache;
    void PollEvents();

};

#endif