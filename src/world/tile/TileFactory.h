#ifndef TILEFACTORY_H
#define TILEFACTORY_H

class TileFactory : public ScriptFactory<Tile>
{
    public:
    static TileFactory* Instance()
    {
        static TileFactory instance;
        return &instance;
    }

    private:
        TileFactory() : ScriptFactory<Tile>("path/to/tiles","Tile");
};

#endif