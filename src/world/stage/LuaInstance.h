#ifndef LUAINSTANCE_H
#define LUAINSTANCE_H

#include "src/world/stage/Instance.h"
#include "src/utils/lua/LuaUniversal.h"

/**
    Purpose: Instance defined by a Lua file.
**/

class LuaInstance : public Instance
{
public:

    LuaInstance(int id) : Instance(id){};

    void _Load() override 
    {
        if(_load_function)
            (*_load_function)(this);
    }

    void _Open() override
    {
        if(_open_function)
            (*_open_function)(this);
    }

    void _Tick(float seconds_elapsed) override
    {   
        if(_update_function)
            (*_update_function)(this,seconds_elapsed);
    }

    void _Close() override 
    {
        if(_close_function)
            (*_close_function)(this);
        //Launch Instance Ended event with information about what to do next
    }

    void _Unload() override
    {
        if(_unload_function)
            (*_unload_function)(this);
    }

    void OnEvent(Event& e) override
    {
        if(_on_event_function)
            (*_on_event_function)(this,e);
        //Listen for stage end condition -owner of stage needs to listen for stage end requests
        Instance::OnEvent(e);
    }

    std::list<Subscription> GetSubscriptions() override
    {
        if(_get_subscriptions_function)
            (*_get_subscriptions_function)(this);

        Instance::GetSubscriptions(); //finish this

    }

    void LoadFromFile(lua_State* lua_state, std::string script_path, std::string instance_name)
    {   
        if (luaL_dofile(lua_state, script_path.c_str()) == 0)
        {
            LuaRef _instance_table = getGlobal(lua_state, instance_name.c_str());
            SetName(instance_name);
            if ((_instance_table).isTable())
            {
                if ((_instance_table)["tile_map"])
                {
                    _tile_map_name = (_instance_table)["tile_map"].cast<std::string>();
                }

                if ((_instance_table)["Open"])
                {
                    _open_function = std::make_unique<LuaRef>((_instance_table)["Open"]);
                }

                if ((_instance_table)["Unload"])
                {
                    _unload_function = std::make_unique<LuaRef>((_instance_table)["Unload"]);
                }

                if ((_instance_table)["Load"])
                {
                    _load_function = std::make_unique<LuaRef>((_instance_table)["Load"]);
                }

                if ((_instance_table)["Update"])
                {
                    _update_function = std::make_unique<LuaRef>((_instance_table)["Update"]);
                }

                if ((_instance_table)["Close"])
                {
                    _close_function = std::make_unique<LuaRef>((_instance_table)["Close"]);
                }

                if ((_instance_table)["OnEvent"])
                {
                    _on_event_function = std::make_unique<LuaRef>((_instance_table)["OnEvent"]);
                }

                if ((_instance_table)["GetSubscriptions"])
                {
                    _get_subscriptions_function = std::make_unique<LuaRef>((_instance_table)["GetSubscriptions"]);
                }

            }
        }
        else
        {
            std::cout << "Error, can't open script: " << script_path << std::endl;
        }        
    }
    private:
        std::unique_ptr<LuaRef> _open_function;
        std::unique_ptr<LuaRef> _update_function;
        std::unique_ptr<LuaRef> _close_function;
        std::unique_ptr<LuaRef> _load_function;
        std::unique_ptr<LuaRef> _unload_function;
        std::unique_ptr<LuaRef> _on_event_function;
        std::unique_ptr<LuaRef> _get_subscriptions_function;
};

#endif