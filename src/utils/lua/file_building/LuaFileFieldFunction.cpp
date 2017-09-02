#include "LuaFileFieldFunction.h"
#include "LuaFileTable.h"

LuaFileFieldFunction::LuaFileFieldFunction(std::string name, LuaFileTable* par) : LuaFileField(name), parent(par)
{
    
}

LuaFileFieldFunction &LuaFileFieldFunction::set_body(std::string &body)
{
    this->body = body;
    return *this;
}

LuaFileFieldFunction &LuaFileFieldFunction::add_param(std::string param)
{
    params.push_back(param);
    return *this;
}

LuaFileTable &LuaFileFieldFunction::end_function()
{
    return *parent;
}

std::string LuaFileFieldFunction::pack()
{
    std::string block = "";
    block += key + " = " + "function(";

    for (auto it = params.begin(); it != params.end(); it++)
    {
        block += *it;
        auto next = std::next(it);
        if (next != params.end())
            block += ",";
    }

    block += ")";
    block += "\n\t";
    block += body;
    block += "\n";
    block += "end";
    return block;
}