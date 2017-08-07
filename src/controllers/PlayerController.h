#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

class PlayerController 
{
    public:
    PlayerController(int id) : _id(id){};

    virtual bool Jump() = 0; 
    virtual bool Left() = 0; 
    virtual bool Right() = 0; 
    virtual bool Action() = 0; 
    int ID(){return _id;}

    private:
        int _id;
};
#endif