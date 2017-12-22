#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <SFML/System/Vector2.hpp>
#include "src/utils/sfml/SFMLUtils.h"

inline bool ClickInBoundingBox(int world_x, int world_y, int x_cent, int y_cent, int width, int height)
{
    sf::Vector2f world_pos (world_x,world_y);

    sf::Vector2f corner_top_left(x_cent - width / 2.0, y_cent - height / 2.0);
    sf::Vector2f corner_top_right(x_cent + width / 2.0, y_cent - height / 2.0);
    sf::Vector2f corner_bot_right(x_cent + width / 2.0, y_cent + height / 2.0);

    sf::Vector2f top_edge = corner_top_right - corner_top_left;    //AB
    sf::Vector2f right_edge = corner_bot_right - corner_top_right; //BC

    sf::Vector2f top_left_to_click = world_pos - corner_top_left;   //AM
    sf::Vector2f top_right_to_click = world_pos - corner_top_right; //BM

    float dot_top_click = sf::Dot(top_edge, top_left_to_click);
    float dot_top_top = sf::Dot(top_edge, top_edge);
    float dot_right_click = sf::Dot(right_edge, top_right_to_click);
    float dot_right_right = sf::Dot(right_edge, right_edge);

    if (0 <= dot_top_click && dot_top_click <= dot_top_top &&
        0 <= dot_right_click && dot_right_click <= dot_right_right)
    {
        return true;
    }
    return false;
};

#endif