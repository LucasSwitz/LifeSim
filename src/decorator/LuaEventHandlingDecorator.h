#ifndef LUAEVENTHANDLINGDECORATOR_H
#define LUAEVENTHANDLINGDECORATOR_H

#include <memory>
#include "src/utils/lua/LuaUniversal.h"
#include "src/event/EventSubscriber.h"
#include "src/decorator/EventHandlingDecorator.h"

class LuaEventHandlingDecorator : public EventHandlingDecorator
{
    public:
        std::list<Subscription> GetSubscriptions() override;
        void OnEvent(Event& e) override;
        static LuaEventHandlingDecorator* FromLuaRef(const LuaRef& parent_table, const LuaRef& event_handling_table);

    private:
        std::unique_ptr<luabridge::LuaRef> _on_event_function;
        std::unique_ptr<luabridge::LuaRef> _get_subscriptions_function;
        std::shared_ptr<luabridge::LuaRef> _parent_table;
};
#endif