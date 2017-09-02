#include <list>
#include "LuaFileField.h"

#ifndef LUAFILEFIELDFUNCTION
#define LUAFILEFIELDFUNCTION

class LuaFileTable;
class LuaFileFieldFunction : public LuaFileField
{

  public:
    LuaFileFieldFunction(std::string name, LuaFileTable *par = nullptr);
    LuaFileFieldFunction &set_body(std::string &body);
    LuaFileFieldFunction &add_param(std::string param);

    LuaFileTable &end_function();

    std::string pack();

    std::string body = "";
    std::list<std::string> params;
    LuaFileTable *parent = nullptr;
};

#endif