#include "Entity.h"
int Entity::_lastId = -1;


bool Entity::HasAttribute(std::string name)
{
    return _attributes.find(name) != _attributes.end();
}

int Entity::GetAttribute(std::string name)
{
    if(HasAttribute(name))
        return _attributes.at(name);
    else
        return 0;
}

void Entity::AddAttribute(std::string name, int value)
{
    auto it = _attributes.find(name);
    if(it == _attributes.end())
        _attributes.insert(std::make_pair(name,value));
    else
        it->second = value;
}

int Entity::ID()
{
    return _id;
}