#ifndef SCRIPTABLESYSTEM_H
#define SCRIPTABLESYSTEM_H

#include <memory>
#include <iostream>
#include "src/utils/lua/LuaUniversal.h"
#include "src/system/System.h"
#include "src/event/Event.h"
#include "src/utils/lua/LuaDefinedAsset.h"

/**
    Lua defined System. When event or Update is called, the LuaRef of the 
    instance ScriptableSystem is passed to lua.
**/

template <typename T>
class ScriptableSystem : public System<T>, public LuaDefinedAsset
{
public:
  ScriptableSystem(){};

  void OnEvent(Event &e)
  {
    if (_on_event_function)
      (*_on_event_function)(*_system_table, e);
  }

  std::list<Subscription> GetSubscriptions()
  {
    std::list<Subscription> subscriptions = System<T>::GetSubscriptions();

    if (_get_subscriptions_function)
    {
      LuaRef lua_subs = (*_get_subscriptions_function)();
      std::list<Subscription> lua_subs_list;
      LuaUniversal::ListFromTable<Subscription>(lua_subs, lua_subs_list);
      subscriptions.splice(std::end(subscriptions), lua_subs_list);
    }

    return subscriptions;
  }

  void Update(float seconds_elapsed, T *g)
  {
    if (_update_function)
      (*_update_function)(*_system_table, seconds_elapsed, g);
  }

protected:
  void _LoadScript(luabridge::lua_State *L, const std::string &system_name)
  {
    using namespace luabridge;
    this->_name = system_name;
    _system_table = std::make_shared<LuaRef>(getGlobal(L, system_name.c_str()));
    if (_system_table->isTable())
    {
      if ((*_system_table)["Update"].isFunction())
      {
        _update_function = std::make_unique<LuaRef>((*_system_table)["Update"]);
      }

      if ((*_system_table)["after"].isString())
      {
        this->_after = (*_system_table)["after"].cast<std::string>();
      }

      if ((*_system_table)["EventHandler"])
      {
        LuaRef event_table = (*_system_table)["EventHandler"];
        if (event_table["OnEvent"])
        {
          _on_event_function = std::make_unique<LuaRef>(event_table["OnEvent"]);
        }
        if (event_table["GetSubscriptions"])
        {
          _get_subscriptions_function = std::make_unique<LuaRef>(event_table["GetSubscriptions"]);
        }
      }
    }
  }

private:
  std::unique_ptr<LuaRef> _update_function;
  std::shared_ptr<LuaRef> _system_table;
  std::shared_ptr<LuaRef> _on_event_function;
  std::shared_ptr<LuaRef> _get_subscriptions_function;
};
#endif