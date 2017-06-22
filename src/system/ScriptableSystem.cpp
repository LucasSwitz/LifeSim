#include "ScriptableSystem.h"

void ScriptableSystem::Update(double seconds_elapsed)
{
    if (_update_function)
        (*_update_function)(*_system_table, seconds_elapsed);
}

void ScriptableSystem::LoadScript(luabridge::lua_State *L, const std::string &script_path, const std::string &system_name)
{
    using namespace luabridge;
    _name = system_name;

    if (luaL_dofile(L, script_path.c_str()) == 0)
    {
        _system_table = std::make_unique<LuaRef>(getGlobal(L, system_name.c_str()));
        if (_system_table->isTable())
        {
            if((*_system_table)["EventHandler"])
            {
                ConfigureEventHandling((*_system_table)["EventHandler"]);
            }
            if ((*_system_table)["Update"].isFunction())
            {
                _update_function = std::make_unique<LuaRef>((*_system_table)["Update"]);
            }

            if ((*_system_table)["after"].isString())
            {
                _after = (*_system_table)["after"].cast<std::string>();
            }
        }
    }
    else
    {
        std::cout << "Error, can't open script: " << script_path << std::endl;
    }
}

void ScriptableSystem::ConfigureEventHandling(LuaRef& event_handler_table)
{
    if (event_handler_table->isTable())
        {
            if(event_handler_table["OnEvent"])
            {
                _on_event_function = std::make_unique<LuaRef>(event_handler_table["OnEvent"]);
            }
            if (event_handler_table["GetSubscriptions"].isFunction())
            {
                _on_event_function = std::make_unique<LuaRef>(event_handler_table["GetSubscriptions"]);
            }
        }
}

void ScriptableSystem::OnEvent(Event& e)
{
    {
        if(_on_event_function)
        {
            (*_on_event_function)(this,e);
        }
    }
}

std::list<Subscritpion> ScriptableSystem::GetSubscriptions()
{
    std::list<Subscritpion> subscriptions = System::GetSubscriptions();

    if(_get_subscriptions_function)
    {
        LuaRef lua_subs = (*get_subscriptions_function)(this);
        std::list<Subscription> lua_subs_list = LuaUniversal.ListFromTable<Subscritpion>(lua_subs);
        subscriptions.merge(lua_subs_list);
    }

    return subscriptions;
}