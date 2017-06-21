#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include "src/component/ComponentUser.h"
class Entity : public ComponentUser
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