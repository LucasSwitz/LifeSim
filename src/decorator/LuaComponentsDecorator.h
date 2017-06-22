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
        std::list<LuaRef> components;
        LuaUniversal::ListFromTable<LuaRef>(component_table, components);

        for (auto it = components.begin(); it != components.end(); it++)
        {
            if ((*it).isTable())
            {
                LuaComponent *component = new LuaComponent();
                component->ConfigureFromLua(*it);
                d->AddComponent(component);
            }
        }
        return d;
    }
};
#endif