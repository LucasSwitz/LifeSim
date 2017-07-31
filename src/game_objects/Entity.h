#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include "src/component/ComponentUser.h"
#define ENTITY_ID_START 0

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
    Entity(int type = 0, std::string _prototype_name="", int id = -1);
    virtual void Tick(){};
    static int _lastId;

    bool IsType(int type) const;
    std::string& GetPrototypeName();
    Entity* Clone();

    static Entity* DowncastFromComponentUser(ComponentUser* caster);

    static int CPP_DEFINED_ENTITY;
    static int LUA_DEFINED_ENTITY;

protected:
    void SetID(int id);
    void SetPrototypeName(std::string& name);

private:
    int _type;
    std::string _prototype_name;
};
#endif