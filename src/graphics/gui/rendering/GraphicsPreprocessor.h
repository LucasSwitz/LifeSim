#ifndef GRAPHICSPREPROCESSOR_H
#define GRAPHICSPREPROCESSOR_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "src/component/ComponentUser.h"
#include "src/world/tile/Tile.h"

class GraphicsPreprocessor
{
  public:
    void ProcessComponentUser(ComponentUser* user, ptr<sf::Texture> texture, ptr<sf::Sprite> sprite)
    {
        float width = user->GetComponentValueFloat("Graphics", "width");
        float height = user->GetComponentValueFloat("Graphics", "height");
        float scale_x = width / texture->getSize().x;
        float scale_y = height / texture->getSize().y;

        bool invert = user->GetComponentValueBool("Graphics", "invert");

        sprite->setTexture(*texture);
        sprite->setScale(scale_x, scale_y);
        sprite->setPosition(user->GetComponentValueFloat("Position", "x") - width/2.0,
                            user->GetComponentValueFloat("Position", "y") - height/2.0); 
       if (invert)
       {
            sprite->setScale(-scale_x, scale_y);
            sprite->setOrigin({sprite->getLocalBounds().width, 0});
       }
        // Extra Settings
        if (user->GetComponent("Graphics")->HasFloatValue("opacity"))
        {
            float opacity = user->GetComponentValueFloat("Graphics", "opacity");
            sprite->setColor(sf::Color(255, 255, 255, opacity * 255));
        }
    }
};

#endif