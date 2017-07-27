#include "src/world/stage/Instance.h"
int Instance::last_id = -1;

Instance::Instance(int id) : _id(id)
{
    if (_id == -1)
    {
        _id = last_id++;
    }
}