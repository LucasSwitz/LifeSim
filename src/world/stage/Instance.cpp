#include "src/world/stage/Instance.h"
int Instance::last_id = 0;

Instance::Instance(int id) : _id(id)
{
    
    _id = last_id;
    last_id++;
}