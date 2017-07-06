#ifndef STAGE_H
#define STAGE_H

#include "event/EventSubscriber.h"

/*Manages a specific game level, Can load and unload systems from the SystemController*/

class Stage : public EventSubscriber
{

    virtual void Load()
    {

    }

    virtual void Start()
    {

    }

    virtual void Update()
    {

    }

    virtual void End()
    {
        //Launch StageEnd event with information about what to do next
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
        std::string name;
};


#endif