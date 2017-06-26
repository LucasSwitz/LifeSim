#ifndef LUACOMPONENT_H
#define LUACOMPONENT_H

#include "src/component/Component.h"
#include "src/utils/lua/LuaUniversal.h"

/**
  LuaComponets are Components loaded from Lua files. They can be configured with a LuaRef. 
**/
class LuaComponent : public Component
{
  public:
    LuaComponent(std::string name="") : Component(name) {}

    void FromLuaRef(const LuaRef &ref);
};

#endif