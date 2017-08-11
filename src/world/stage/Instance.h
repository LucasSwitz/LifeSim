#ifndef INSTANCE_H
#define INSTANCE_H

#include "src/event/EventSubscriber.h"
#include "src/world/tile/TileMap.h"
#include "src/game_objects/Entity.h"
#include "src/event/Event.h"
#include "src/game/FPSRunnable.h"
#include "src/game_objects/EntityManager.h"

/*
    Purpose: Instances describe the currently rendering tile map, and handles the transition to
             other instances. When an instance goes out of scope it may allow all live entities
             contained to remain operating, but must disable their graphics componenets. 
*/

class Instance : public EventSubscriber, public FPSRunnable
{
 public:

    Instance(int id = -1);

    Instance(const Instance& instance)
    {}

    ~Instance()
    {
        _tile_map.Erase();
    }

    virtual void Load() override
    {
        //load all local entites, do a cutscene, whatevs
        if(!_tile_map_name.empty())
        {
            _tile_map.LoadFromFile(_tile_map_name);
        }
        else
        {
            std::cout << "TileMap already loaded!" << std::endl;
        }
        _loaded = true;
    }

    virtual void Unload() override
    {
        //delete all local entities
        _tile_map.Unload();
        _loaded = false;
    }

    virtual void Open()
    {
        _tile_map.Show();

        for(int& i: _local_entities)
        {
            Entity* e = EntityManager::Instance()->GetEntityByID(i);
            e->EnableComponent("Graphics");
        }
        _open = true;   
    }

    virtual void Tick(float seconds_elapsed) override
    {
        
    }

    virtual void Close()
    {
        _tile_map.Hide();

        //should have different options for what components to remove at different levels of closing.
        for(int& i: _local_entities)
        {
            Entity* e = EntityManager::Instance()->GetEntityByID(i);
            e->DisableComponent("Graphics");
        }      
        _open = false;
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

    TileMap& GetTileMap()
    {
        return _tile_map;
    }

    void SetTileMap(TileMap map)
    {   
        _tile_map.Erase();
        _tile_map = map;
    }   

    int GetID()
    {
        return _id;
    }

    bool IsOpen()
    {
        return _open;
    }

    bool IsLoaded()
    {
        return _loaded;
    }

    void SetID(int id)
    {
        _id = id;
    }

    void SetName(const std::string& name)
    {
        _name = name;
    }

    std::string& GetName()
    {
        return _name;
    }


    protected:
        std::string _name;
        std::string _tile_map_name = "";
        int _id;
        static int last_id;
    private:
        TileMap _tile_map;
        std::list<int> _local_entities;
        bool _loaded;
        bool _open;
        
};
#endif