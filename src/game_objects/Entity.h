#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include "src/component/ComponentUser.h"

/**
    Entities are simply ComponentLists with integer IDs attached to them.
    They can be accessed by querying the EntityManager with a specified
    ID.
**/
class Entity : public ComponentUser
{ 
    friend class EntityManager;

public:
    virtual ~Entity();
    Entity(int type);
    virtual void Tick(){};
    static int _lastId;

    int ID() const;
    bool IsType(int type);

    static int CPP_DEFINED_ENTITY;
    static int LUA_DEFINED_ENTITY;

protected:

    void SetID(int id);
private:
    int _id;
    int _type;
};
#endif