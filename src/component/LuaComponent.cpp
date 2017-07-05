#include "LuaComponent.h"

void LuaComponent::FromLuaRef(const LuaRef &ref)
{   
    std::unordered_map<std::string, LuaRef> values = LuaUniversal::KeyValueMapFromTable(ref);
    for (auto it : values)
    {
        std::string key = it.first;
        LuaRef value = it.second;

        if (value.isNumber())
        {
            AddValue(key, value.cast<float>());
        }
        else if (value.isString())
        {
            AddValue(key, value.cast<std::string>());
        }
        else if (value.isBoolean())
        {
            AddValue(key, value.cast<bool>());
        }
        else if (value.isTable())
        {
            LuaComponent* component = new LuaComponent(key);
            component->FromLuaRef(value);
            AddSubcomponent(component);
        }
    }
}