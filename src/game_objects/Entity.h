


class Entity
{
public:
    Entity()
    {
        lastId++;
        id = lastId; 
    }

private:
    static lastId; 
    int _id;
}