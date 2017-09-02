#ifndef LUAFILEPRIMITIVES_H
#define LUAFILEPRIMITIVES_H

#include "LuaFileField.h"

class LuaFileFieldString : public LuaFileField
{
  public:
    LuaFileFieldString(std::string name, std::string val) : LuaFileField(name), value(val){};
    std::string value;
    virtual std::string pack()
    {
        return key + " = " + "\"" + value + "\"";
    }
};

class LuaFileFieldNumber : public LuaFileField
{
  public:
    LuaFileFieldNumber(std::string name) : LuaFileField(name){};
    float value;
    virtual std::string pack()
    {
        return key + " = " + std::to_string(value);
    }
};

class LuaFileFieldBool : public LuaFileField
{
  public:
    LuaFileFieldBool(std::string name) : LuaFileField(name){};
    bool value;
    virtual std::string pack()
    {
        return key + " = " + std::to_string(value);
    }
};

#endif