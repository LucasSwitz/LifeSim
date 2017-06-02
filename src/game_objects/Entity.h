#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
    virtual void Tick(){};
    static int _lastId; 

protected:
    Entity()
    {
        _lastId++;
        _id = _lastId; 
    }

private:
    int _id;
};

#endif