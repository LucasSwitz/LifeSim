#ifndef STAGE_H
#define STAGE_H

#include "event/EventSubscriber.h"

/*Manages a specific game level, Can load and unload systems from the SystemController*/

class Instance : public EventSubscriber
{

    virtual void Load()
    {
        //load all local entites, do a cutscene, whatevs
    }

    virtual void Unload()
    {
        //delete all local entities
    }

    virtual void Open()
    {
        for(Entity* e: _local_entities)
        {
            e->EnableComponent("Graphics");
        }

        for(Tile* t: _tile_map.tiles())
        {
            t->EnableComponent("Graphics");
        }
    }

    virtual void Update(double seconds_elapsed)
    {
        
    }

    virtual void Close()
    {
        for(Entity* e : _local_entites)
        {
            e->DisableComponent("Graphics");
        }
            for(Tile* t: _tile_map.tiles())
        {
            t->DisableComponent("Graphics");
        }
    }

    virtual void OnEvent(Event& e)
    {
        //Listen for stage end condition -owner of stage needs to listen for stage end requests
    }

    std::list<Subscription> GetSubscriptions()
    {

    }

    void SetTileMap(std::string file_name)
    {
        _tile_map.LoadFromFile(file_name);
    }

    private:
        TileMap _tile_map;
        std::list<Entity*> _local_entites;
        std::string name;
};


#endif