#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>

class System
{
  public:
    virtual void Update() = 0;

    std::string GetName() const
    {
        return _name;
    }
    
    std::string GetAfter() const
    {
        return _after;
    }

  protected:
    System(std::string name = "") : _name(name){};
    std::string _name = "";
    std::string _after = "";
};

#endif