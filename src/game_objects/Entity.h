#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>

class Entity
{
    friend class EntityManager;

public:
    virtual void Tick(){};
    static int _lastId;
    bool HasAttribute(std::string name);
    int GetAttribute(std::string name);
    int ID();

protected:
    Entity();

    void AddAttribute(std::string name, int value);

private:
    int _id;
    std::unordered_map<std::string, int> _attributes;
};

#endif