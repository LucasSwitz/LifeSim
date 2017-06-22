#ifndef SCRIPTABLESYSTEM_H
#define SCRIPTABLESYSTEM_H

#include <memory>
#include <iostream>
#include "src/utils/lua/LuaUniversal.h"
#include "src/system/System.h"
#include "src/event/Event.h"
#include "src/event/EventManager.h"

class ScriptableSystem : public System
{
    public:
    ScriptableSystem(){};

    void Update(double seconds_elapsed) override;

    void LoadScript(luabridge::lua_State *L, const std::string &script_path, const std::string &system_name);

    std::list<Subscription> GetSubscriptions() override;

    void OnEvent(Event& e) override;

private:
        std::unique_ptr<luabridge::LuaRef> _update_function;
        std::unique_ptr<luabridge::LuaRef> _system_table;
        std::unique_ptr<luabridge::LuaRef> _on_event_function;
        std::unique_ptr<luabridge::LuaRef> _get_subscriptions_function;

        void ConfigureEventHandling(const LuaRef& event_handler_table);
};
#endif