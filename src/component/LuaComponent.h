#ifndef LUACOMPONENT_H
#define LUACOMPONENT_H

#include "src/component/Component.h"
#include "src/utils/lua/LuaUniversal.h"

class LuaComponent : public Component
{
  public:
    LuaComponent(std::string name) : Component(name) {}

    void ConfigureFromLua(LuaRef &ref)
    {
        std::unordered_map<std::string, LuaRef> values = LuaUniversal::KeyValueMapFromTable(ref);
        for (auto it : values)
        {
            std::string name = it.first;
            LuaRef value = it.second;

            if (value.isNumber())
            {
                AddValue(name, value.cast<float>());
            }
            else if (value.isString())
            {
                AddValue(name, value.cast<std::string>());
            }
        }
    }
};

#endif