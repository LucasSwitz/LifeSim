#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include "src/utils/Globals.h"

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

class TextureCache
{
public:
    bool TextureCached(std::string name);
    bool LoadTexture(std::string name);
    ptr<sf::Texture> GetTexture(std::string name);

private:
    std::unordered_map<std::string, ptr<sf::Texture>> _texture_cache;

};
#endif