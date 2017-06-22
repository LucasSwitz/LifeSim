#include "LuaEventHandlingDecorator.h"
LuaEventHandlingDecorator* LuaEventHandlingDecorator::FromLuaRef(const LuaRef& parent_table, const LuaRef& event_handler_table)
{
    LuaEventHandlingDecorator* d = new LuaEventHandlingDecorator();

    d->_parent_table = std::make_shared<LuaRef>(parent_table);

    if (event_handler_table.isTable())
    {
        if (event_handler_table["OnEvent"])
        {
            d->_on_event_function = std::make_unique<LuaRef>(event_handler_table["OnEvent"]);
        }
        if (event_handler_table["GetSubscriptions"].isFunction())
        {
            d->_get_subscriptions_function = std::make_unique<LuaRef>(event_handler_table["GetSubscriptions"]);
        }
    }

    return d;
}

void LuaEventHandlingDecorator::OnEvent(Event &e)
{
    {
        if (_on_event_function)
        {
            (*_on_event_function)(*_parent_table, e);
        }
    }
}

std::list<Subscription> LuaEventHandlingDecorator::GetSubscriptions()
{
    std::list<Subscription> subscriptions = EventHandlingDecorator::GetSubscriptions();

    if (_get_subscriptions_function)
    {
        LuaRef lua_subs = (*_get_subscriptions_function)();
        std::list<Subscription> lua_subs_list;
        LuaUniversal::ListFromTable<Subscription>(lua_subs, lua_subs_list);
        subscriptions.splice(std::end(subscriptions), lua_subs_list);
    }

    return subscriptions;
}