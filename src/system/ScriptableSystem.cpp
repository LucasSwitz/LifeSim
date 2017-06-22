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
                EventManager::Instance()->RegisterSubscriber(this);
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

void ScriptableSystem::ConfigureEventHandling(const LuaRef& event_handler_table)
{
    if (event_handler_table.isTable())
        {
            if(event_handler_table["OnEvent"])
            {
                _on_event_function = std::make_unique<LuaRef>(event_handler_table["OnEvent"]);
            }
            if (event_handler_table["GetSubscriptions"].isFunction())
            {
                _get_subscriptions_function = std::make_unique<LuaRef>(event_handler_table["GetSubscriptions"]);
            }
        }
}

void ScriptableSystem::OnEvent(Event& e)
{
    {
        if(_on_event_function)
        {
            (*_on_event_function)(e);
        }
    }
}

std::list<Subscription> ScriptableSystem::GetSubscriptions()
{
    std::list<Subscription> subscriptions = System::GetSubscriptions();

    if(_get_subscriptions_function)
    {
        LuaRef lua_subs = (*_get_subscriptions_function)();
        std::list<Subscription> lua_subs_list;
        LuaUniversal::ListFromTable<Subscription>(lua_subs, lua_subs_list);
        subscriptions.splice(std::end(subscriptions),lua_subs_list);
    }

    return subscriptions;
}