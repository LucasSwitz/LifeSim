#ifndef LUATILEFACTORY_H
#define LUATILEFACTORY_H

#include "src/utils/ScriptFactory.h"
#include "src/world/tile/LuaTile.h"
#include "src/utils/lua/LuaUniversal.h"

class LuaTileFactory : public ScriptFactory<std::string>
{

  public:
  bool TilePrototypeExists(std::string name);
  bool TilePrototypeExists(int id);
  Tile* GetTile(std::string name);
  Tile* GetTile(int id);
  const std::unordered_map<int,std::string>& GetAllTiles();
  const std::unordered_map<int,std::string>& GetAllTileIndentifiers();
  void AddScript(Preamble &pre, std::string script_path) override;

  void Reset() override;

  static LuaTileFactory* Instance()
  {
    static LuaTileFactory instance("/home/pabu/Desktop/LifeSim/lua_scripts/world/tiles", "Tile");

    return &instance;
  }

protected:
  LuaTileFactory(std::string tile_scripts_path, std::string script_type) 
                        : ScriptFactory<std::string>(tile_scripts_path, script_type){};
    
private:    
    std::unordered_map<int, std::string> _tile_directory;
    std::unordered_map<std::string, int> _tile_name_to_id_directory;
    std::unordered_map<int, std::string> _tile_id_to_name_directory;

};

#endif
