#ifndef GRAPHICSPREPROCESSOR_H
#define GRAPHICSPREPROCESSOR_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "src/component/ComponentUser.h"
#include "src/world/tile/Tile.h"

class GraphicsPreprocessor
{
    public:
    void ProcessComponentUser(ComponentUser *user, sf::Texture* texture, sf::Sprite* sprite)
    {
        float scale_x = (float)TILE_WIDTH / texture->getSize().x;
        float scale_y = (float)TILE_HEIGHT / texture->getSize().y;

        sprite->setScale(scale_x, scale_y);
        sprite->setTexture(*texture);
        sprite->setPosition(user->GetComponentValueFloat("Position", "x") - sprite->getGlobalBounds().width / 2.0,
                             user->GetComponentValueFloat("Position", "y") - sprite->getGlobalBounds().height / 2.0);

        // Extra Settings
        if(user->GetComponent("Graphics")->HasFloatValue("opacity"))
        {
            float opacity = user->GetComponentValueFloat("Graphics","opacity");
            sprite->setColor(sf::Color(255,255,255,opacity*255));
        } 
    }
};

#endif