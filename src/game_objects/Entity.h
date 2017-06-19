#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include "src/component/Component.h"

class Entity
{
    friend class EntityManager;

public:
    virtual void Tick(){};
    static int _lastId;
    bool HasAttribute(std::string name);
    int GetAttribute(std::string name);
    void AddComponent(Component* component);
    void RemoveComponent(std::string name);
    bool HasComponent(std::string name);
    void AddAttribute(std::string name, int value);
    const Component* GetComponent(std::string name);

    int ID();

protected:
    Entity();
    void SetID(int id);

    std::unordered_map<std::string, Component*> _components;


private:
    int _id;
    std::unordered_map<std::string, int> _attributes;

};

#endif