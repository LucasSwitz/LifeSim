#ifndef GRAPHICSPREPROCESSOR_H
#define GRAPHICSPREPROCESSOR_H

#include <SFML/Graphics/Sprite.hpp>

class GraphicsPreProcessor
{
    void ProcessComponentUser( ComponentUser *user, Texture* texture, sf::Sprite* sprite)
    {
        double scale_x = (float)TILE_WIDTH / texture->getSize().x;
        double scale_y = (float)TILE_HEIGHT / texture->getSize().y;
        sprite->setScale(scale_x, scale_y);
        sprite->setTexture(*texture);
        sprite->setPosition(user->GetComponentValueFloat("Position", "x") - sprite->getGlobalBounds().width / 2.0,
                             user->GetComponentValueFloat("Position", "y") - sprite->getGlobalBounds().height / 2.0);

        // Extra Settings
        if(user->HasComponent("Graphics","opacity"))
        {
            float opacity = user->GetComponentValueFloat("Graphics","Opacity");
            sprite->setColor(255,255,255,opacity*255);
        } 
    }
};

#endif