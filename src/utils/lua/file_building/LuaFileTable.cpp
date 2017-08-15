#include "LuaFileFieldFunction.h"
#include "LuaFileTable.h"

LuaFileFieldFunction &LuaFileTable::add_function(std::string name)
{
    LuaFileFieldFunction *function = new LuaFileFieldFunction(name, this);
    fields.push_back(function);
    return *function;
}

LuaFileTable &LuaFileTable::add_primitive_field(LuaFileField *field)
{
    fields.push_back(field);
    return *this;
}

LuaFileTable &LuaFileTable::end_table()
{
    return *parent;
}

LuaFileTable &LuaFileTable::add_table(std::string &key)
{
    LuaFileTable *table = new LuaFileTable(key, this);
    return *table;
}

std::string LuaFileTable::pack()
{
    std::string out = key + " = \n { \n";

    for (auto it = fields.begin(); it != fields.end(); it++)
    {
        out += (*it)->pack();
        out += ", \n";
    }

    out += "}";

    return out;
}