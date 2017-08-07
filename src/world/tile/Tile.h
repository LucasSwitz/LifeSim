#ifndef TILE_H
#define TILE_H

#include "src/component/ComponentUser.h"

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

/**
    Purpose: A Tile is described by a position and graphic. Tiles can be used as the building
    blocks for an Instance. Although the most basic tiles simply define position and grapic
    components, tiles can take on any component nessesary. This leaves many options for creative
    tile effects. 
**/
class Tile : public ComponentUser
{
  public:
    Tile(int id, std::string name) : _id(id), _name(name) {}
    int GetID()
    {
        return _id;
    }
    std::string GetName()
    {
        return _name;
    }
    virtual ~Tile(){};

    Tile *Clone()
    {
        Tile *t = new Tile(_id, _name);
        std::unordered_map<std::string, Component *> components = GetAllComponents();
        for (auto it = components.begin(); it != components.end(); it++)
        {
            Component *c = new Component(*(it->second));
            t->AddComponent(c);
        }

        return t;
    }

  private:
    int _id;
    std::string _name;
};

#endif