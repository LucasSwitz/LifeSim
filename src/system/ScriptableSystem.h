#ifndef SCRIPTABLESYSTEM_H
#define SCRIPTABLESYSTEM_H

#include <memory>
#include <iostream>
#include "src/utils/lua/LuaUniversal.h"
#include "src/event/messaging/MessageDispatch.h"
#include "src/system/System.h"
#include "src/event/Event.h"

/**
    Lua defined System. When event or Update is called, the LuaRef of the 
    instance ScriptableSystem is passed to lua.
**/

class ScriptableSystem : public System
{
    public:
    ScriptableSystem(){};

    void Update(float seconds_elapsed) override;
    void LoadScript(lua_State *L, const std::string &script_path, const std::string &system_name);
    void OnEvent(Event& e) override;
    std::list<Subscription> GetSubscriptions() override;

private:
        std::unique_ptr<LuaRef> _update_function;
        std::shared_ptr<LuaRef> _system_table;
        std::shared_ptr<LuaRef> _on_event_function;
        std::shared_ptr<LuaRef> _get_subscriptions_function;
};
#endif