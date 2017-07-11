#include "TextureCache.h"
#include "src/utils/logging/Logging.h"


sf::Texture* TextureCache::GetTexture(std::string name)
{
    if(TextureCached(name) || LoadTexture(name))
    {
        return _texture_cache.at(name);
    }
    else
    {
        LOG->LogFile("Failed to Get texture: " + name);
        return nullptr;
    }
}

bool TextureCache::TextureCached(std::string name)
{
    return _texture_cache.find(name) != _texture_cache.end();
}

bool TextureCache::LoadTexture(std::string file_path)
{
    sf::Texture* texture = new sf::Texture();
    if(texture->loadFromFile(file_path))
    {
        _texture_cache.insert(std::make_pair(file_path,texture));
        LOG->LogOverlay("Succesfully Loaded Texture: " + file_path);
        LOG->LogFile("Succesfully Loaded Texture: " + file_path);
        return true;
    }
    else
    {
        LOG->LogFile("Failed to load texture: " + file_path);
        delete texture;
        return false;
    }
}