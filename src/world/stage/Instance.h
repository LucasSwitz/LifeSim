#ifndef INSTANCE_H
#define INSTANCE_H

#include "src/event/EventSubscriber.h"
#include "src/world/tile/TileMap.h"
#include "src/game_objects/Entity.h"
#include "src/event/Event.h"
#include "src/game/FPSRunnable.h"
#include "src/game_objects/EntityManager.h"
#include "src/utils/math/Point.h"

/*
    Purpose: Instances describe the currently rendering tile map, and handles the transition to
             other instances. When an instance goes out of scope it may allow all live entities
             contained to remain operating, but must disable their graphics componenets. 
*/
class SpacialPartitioningGrid;

class Instance : public EventSubscriber, public FPSRunnable
{
 public:
    Instance(int id = -1,std::string name = "");

    Instance(const Instance& instance): _anchor_point(0,0){}

    ~Instance()
    {
        _tile_map.Erase();
    }

    void Load(ComponentUserBase& component_user_base)
    {
        if(!_tile_map_name.empty() && !_loaded)
        {
            _tile_map.LoadFromFile(_tile_map_name);
        }
        else
        {
            std::cout << "TileMap already loaded or no file given!" << std::endl;
        }

        // make component user base aware of these tiles
        for(auto row : _tile_map.GetTiles())
        {
            for(ptr<Tile> tile : row)
            {                
                component_user_base.AddComponentUser(tile);
            }
        }
        
        _Load();

        _loaded = true;
    }

    virtual void Load(){
        _Load();
        _loaded = true;
    }

    virtual void Unload(ComponentUserBase& component_user_base, EntityManager& em)
    {
        /*for(auto row : _tile_map.GetTiles())
        {
            for(ptr<Tile> tile : row)
            {                
                component_user_base.DeRegister(*(tile.get()));
            }
        }*/

        for(int id : _local_entities)
        {
            ptr<Entity> e = em.GetEntityByID(id);
            em.DeregisterEntity(id);
            component_user_base.DeRegister(*(e.get()));
        }

        _Unload();

        _loaded = false;
    }

    virtual void Unload() override{
        //delete all local entities
        _tile_map.Unload();
        _Unload();

        _loaded = false;

    }

    virtual void Open(EntityManager& em){
        if(!_loaded)
        { 
            Load();
        }

        _tile_map.Show();

        for(int& i: _local_entities)
        {
            ptr<Entity> e = em.GetEntityByID(i);
            e->EnableAll();
        }

        _Open();

        _open = true;   
    }

    virtual void Tick(float seconds_elapsed) override{
        _Tick(seconds_elapsed);
    }

    int GetWidth() const{
        return _tile_map.WidthPx();
    }

    int GetHeight() const{
        return _tile_map.HeightPx();
    }

    int GetX() const{
        return _anchor_point.y;
    }

    int GetY() const{
        return _anchor_point.x;
    }

    virtual void Close(EntityManager& em){
        _tile_map.Hide();

        //should have different options for what components to remove at different levels of closing.
        for(int& i: _local_entities)
        {
            ptr<Entity> e = em.GetEntityByID(i);
            e->DisableComponent("Graphics");
        }      

        _Close();

        _open = false;
    }

    virtual void OnEvent(Event& e){
        //Listen for stage end condition -owner of stage needs to listen for stage end requests
    }

    std::list<Subscription> GetSubscriptions(){
    }

    void SetTileMap(std::string file_name){
        _tile_map.LoadFromFile(file_name);
    }

    void SetTileMap(TileMap& map){   
        _tile_map.Erase();
        _tile_map.Copy(map);
    }   

    TileMap& GetTileMap(){
        return _tile_map;
    }

    bool IsOpen(){
        return _open;
    }

    bool IsLoaded(){
        return _loaded;
    }

    void SetName(const std::string& name){
        _name = name;
    }

    std::string& GetName(){
        return _name;
    }

    void AddLocalEntity(int id) {
        _local_entities.push_back(id);
    }

    int& GetID(){
        return _id;
    }

    const Point& GetAnchor(){
        return _anchor_point;
    }

    // These will be called after Instance has finished doing the basics. 
    // These can be used to add implementation specific logic.
    virtual void _Load(){};
    virtual void _Unload(){};
    virtual void _Open(){};
    virtual void _Close(){};
    virtual void _Tick(float seconds_elapsed){};

    protected:
        std::string _name;
        std::string _tile_map_name = "";
        int _id;
    private:
        TileMap _tile_map;
        std::list<int> _local_entities;
        //SpacialPartitioningGrid* _grid; // should look for greater abstraction "GridableInterface?"
        Point _anchor_point;
        bool _loaded = false;
        bool _open = false;
        
};
#endif