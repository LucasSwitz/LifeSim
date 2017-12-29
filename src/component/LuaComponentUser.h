#ifndef LUACOMPONENTUSER_H
#define LUACOMPONENTUSER_H

#include "src/component/ComponentUser.h"
#include "src/utils/lua/LuaUniversal.h"
#include "src/component/LuaComponent.h"

class LuaComponentUser : public ComponentUser
{
    void ConfigureAllComponentsFromLua(const LuaRef &ref)
    {
        std::unordered_map<std::string, LuaRef> components = LuaUniversal::KeyValueMapFromTable(ref);
        for (auto it : components)
        {
            auto key = it.first;
            LuaRef component_ref = it.second;

            ptr<LuaComponent> new_component(new LuaComponent(key));
            new_component->FromLuaRef(component_ref);
            ComponentUser::AddComponent(new_component);
        }
    }
};
#endif