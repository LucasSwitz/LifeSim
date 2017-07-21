#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

class TextureCache
{
public:
    bool TextureCached(std::string name);
    bool LoadTexture(std::string name);
    sf::Texture* GetTexture(std::string name);

private:
    std::unordered_map<std::string, sf::Texture*> _texture_cache;

};
#endif