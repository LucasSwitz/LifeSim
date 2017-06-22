#ifndef LUACOMPONENTNDECORATOR_H
#define LUACOMPONENTNDECORATOR_H

#include "src/decorator/ComponentsDecorator.h"
#include "src/utils/lua/LuaUniversal.h"
#include "src/component/LuaComponent.h"

class LuaComponentsDecorator : public ComponentsDecorator
{
  public:
    static LuaComponentsDecorator *FromLuaRef(const LuaRef &component_table)
    {
        LuaComponentsDecorator* d = new LuaComponentsDecorator();
        std::unordered_map<std::string, LuaRef> components = 
            LuaUniversal::KeyValueMapFromTable(component_table);

        for (auto it = components.begin(); it != components.end(); it++)
        {
            if (it->second.isTable())
            {
                LuaComponent *component = new LuaComponent(it->first);
                component->ConfigureFromLua(it->second);
                d->AddComponent(component);
            }
        }
        return d;
    }
};
#endif