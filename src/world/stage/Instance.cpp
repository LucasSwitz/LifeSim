#include "src/world/stage/Instance.h"
#include "src/world/stage/LuaInstanceFactory.h"
#include "src/game/tools/SpacialPartitioningGrid.h"

Instance::Instance(int id, std::string name) : _id(id), _name(name), _anchor_point(-1,-1) //fixme
{
    _grid = new SpacialPartitioningGrid(this);

    if(_id == -1)
    {
        _id = LuaInstanceFactory::Inst()->LowestUnassignedKey();
    }
}