#include "src/world/stage/Instance.h"
int Instance::last_id = 0;

Instance::Instance(int id, std::string name) : _id(id), _name(name)
{
    if(_id == -1)
    {
        _id = last_id;
        last_id++;
    }
}