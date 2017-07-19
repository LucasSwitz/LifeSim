#ifndef PAINTTILEBRUSHSTATE_H
#define PAINTTILEBRUSHSTATE_H

#include "src/game/gui/brush/BrushState.h"
#include "src/utils/window/WindowUtils.h"


class PaintTileBrushState : public BrushState
{
  public:
    enum PaintingState
    {
        DORMANT,
        PAINTING,
    };

    PaintTileBrushState(Tile* selected) : _selected_tile(selected){};

    void PaintWindow(PMIDGWindow &window) override
    {
        if (_painting_state == PAINTING)
        {
            RenderSelectBox(window);
        }
    }

    bool OnInstanceMouseEvent(sf::Event& e, sf::Vector2f& event_world_position, Instance* instance) override
    {        
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
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

                std::list<Tile *> boxed_tiles;
                
                instance->GetTileMap().TilesInRange(_mouse_history.x1, _mouse_history.y1,
                                                            _mouse_history.x2, _mouse_history.y2,
                                                            boxed_tiles);
                if (_selected_tile)
                {
                    for (Tile *boxed_tile : boxed_tiles)
                    {
                        float x = boxed_tile->GetComponentValueFloat("Position","x");
                        float y = boxed_tile->GetComponentValueFloat("Position","y");
                        delete boxed_tile;
                        boxed_tile = _selected_tile->Clone();
                        boxed_tile->SetComponentValueFloat("Position", "x", x);
                        boxed_tile->SetComponentValueFloat("Position", "y", y);
                    }
                }
                _painting_state = DORMANT;
                return true;
            }
        }
    }

  private:
    void RenderSelectBox(PMIDGWindow &window)
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
        rect.setPosition(pos_x, pos_y);
        window.DrawNow(rect);
    }

    MouseHistory _mouse_history;
    PaintingState _painting_state = DORMANT;
    Tile* _selected_tile;
};
#endif