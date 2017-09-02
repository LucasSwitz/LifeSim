#ifndef LUAFILEFIELD_H
#define LUAFILEFIELD_H

#include <string>

class LuaFileField
{
  public:
    LuaFileField(std::string name) : key(name){};
    std::string key;
    virtual std::string pack() = 0;
};

#endif