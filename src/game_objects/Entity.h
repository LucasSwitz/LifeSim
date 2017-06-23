#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include "src/decorator/LuaDecorated.h"

class Entity : public LuaDecorated
{ 
    friend class EntityManager;

public:
    ~Entity();

    virtual void Tick(){};
    static int _lastId;

    int ID() const;

protected:
    Entity();
    void SetID(int id);
private:
    int _id;
    std::unordered_map<std::string, int> _attributes;

};

#endif