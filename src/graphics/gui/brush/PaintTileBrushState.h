#ifndef PAINTTILEBRUSHSTATE_H
#define PAINTTILEBRUSHSTATE_H

#include "src/graphics/gui/brush/BrushState.h"
#include "src/utils/window/WindowUtils.h"

class PaintTileBrushState : public BrushState
{
  public:
    enum PaintingState
    {
        DORMANT,
        PAINTING,
    };

    PaintTileBrushState(ptr<Tile> selected) : _selected_tile(selected){};

    bool PaintWindow(TBWindow &window) override
    {
        if (_painting_state == PAINTING)
        {
            RenderSelectBox(window);
        }
        return false;
    }

    bool OnGameStateMouseEvent(sf::Event &e, sf::Vector2f &event_world_position, ptr<GameState>  gs, 
        ptr<ComponentUser> c = nullptr) override
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                _instance = gs->GetStage()->GetCurrentInstance(); //TODO: Move this to constructor
                _mouse_history.x1 = event_world_position.x;
                _mouse_history.y1 = event_world_position.y;
                _painting_state = PAINTING;
                return true;
            }
            else if (e.mouseButton.button == sf::Mouse::Right)
            {
                _painting_state = DORMANT;
                return true;
            }
        }
        else if (e.type == sf::Event::MouseButtonReleased)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                _mouse_history.x2 = event_world_position.x;
                _mouse_history.y2 = event_world_position.y;

                if (_selected_tile)
                {
                    for (auto it = _boxed_tiles.begin(); it != _boxed_tiles.end();it++)
                    {
                        ptr<Tile> replaced =  *it;
                        float x = replaced->GetComponentValueFloat("Position", "x");
                        float y = replaced->GetComponentValueFloat("Position", "y");

                        ComponentUserListener* listener = replaced->GetComponentListener();

                        *replaced = *_selected_tile->Clone();
                        replaced->SetComponentValueFloat("Position", "x", x);
                        replaced->SetComponentValueFloat("Position", "y", y);
                        replaced->SetListener(listener);
                        replaced->EnableAll();
                    }

                    _boxed_tiles.clear();
                }
                _painting_state = DORMANT;
                return true;
            }
        }
    }

  private:
    void RenderSelectBox(TBWindow &window)
    {
        sf::Vector2i screen_mouse_position = sf::Mouse::getPosition(window.SFWindow());
        sf::Vector2f world_mouse_position = window.SFWindow().mapPixelToCoords(screen_mouse_position);

        int current_mouse_position_x = world_mouse_position.x;
        int current_mouse_position_y = world_mouse_position.y;

        int delta_x = current_mouse_position_x - _mouse_history.x1;
        int delta_y = current_mouse_position_y - _mouse_history.y1;

        int width = std::abs(delta_x);
        int height = std::abs(delta_y);

        int pos_x = (delta_x < 0 ? current_mouse_position_x : _mouse_history.x1);
        int pos_y = (delta_y < 0 ? current_mouse_position_y : _mouse_history.y1);

        sf::RectangleShape rect(sf::Vector2f(width, height));
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color(255, 255, 255, 100));
        rect.setOutlineThickness(1);
        rect.setPosition(pos_x, pos_y);
        window.DrawNow(rect);

        HighLightBoxedTile(_mouse_history.x1, _mouse_history.y1, current_mouse_position_x, current_mouse_position_y);
    }

    void HighLightBoxedTile(int x1, int y1, int x2, int y2)
    {
        if (_instance)
        {
            for (auto tile : _boxed_tiles)
            {
                tile->SetComponentValueFloat("Graphics", "opacity", 1.0);
            }

            _boxed_tiles.clear();

            _instance->GetTileMap().TilesInRange(x1, y1, x2, y2, _boxed_tiles);

            for (auto tile : _boxed_tiles)
            {
                tile->SetComponentValueFloat("Graphics", "opacity", .9);
            }
        }
    }

    MouseHistory _mouse_history;
    PaintingState _painting_state = DORMANT;
    ptr<Tile> _selected_tile = nullptr;
    ptr<Instance> _instance = nullptr;
    std::list<ptr<Tile>> _boxed_tiles;
};
#endif