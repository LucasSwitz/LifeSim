#ifndef LUAFILETABLE_H
#define LUAFILETABLE_H

#include <list>
#include "LuaFileField.h"
#include "LuaFilePrimitives.h"
#include "LuaFileFieldFunction.h"

class LuaFileFieldFunction;
class LuaFileTable : public LuaFileField
{

  public:
    LuaFileTable(std::string name, LuaFileTable *par = nullptr) : LuaFileField(name), parent(par){};

    LuaFileTable &add_primitive_field(LuaFileField *field);

    LuaFileFieldFunction &add_function(std::string name);

    LuaFileTable &end_table();

    LuaFileTable &add_table(std::string &key);

    std::string pack();

    std::list<LuaFileField *> fields;
    LuaFileTable *parent;
};

#endif