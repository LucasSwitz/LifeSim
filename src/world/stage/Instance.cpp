#include "src/world/stage/Instance.h"
#include "src/world/stage/LuaInstanceFactory.h"
Instance::Instance(int id, std::string name) : _id(id), _name(name)
{
    if(_id == -1)
    {
        _id = LuaInstanceFactory::Inst()->LowestUnassignedKey();
    }
}