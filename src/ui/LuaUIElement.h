#ifndef LUAUIELEMENT_H
#define LUAUIELEMENT_H

#include "src/ui/UIElement.h"
#include "src/utils/lua/LuaUniversal.h"
#include "src/component/LuaComponent.h"
#include "src/utils/lua/LuaDefinedAsset.h"

class LuaUIElement : public UIElement, public LuaDefinedAsset
{
    public:
    LuaUIElement(int _type, std::string name) : UIElement(_type, name){}

    void _LoadScript(lua_State *lua_state, const std::string &entity_name)
    {
        using namespace luabridge;

        auto ui_element_table = std::make_shared<LuaRef>(getGlobal(lua_state, entity_name.c_str()));
        if ((*ui_element_table).isTable())
        {
            if ((*ui_element_table)["Components"])
            {
                LuaRef components_table = (*ui_element_table)["Components"];
                ConfigureAllComponentsFromLua(components_table);
            }
        }
    }

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

        std::cout << "Configured all components" << std::endl;
    }
};
#endif