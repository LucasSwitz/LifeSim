#ifndef LUASTAGE_H
#define LUASTAGE_H

class LuaInstance : public Instance
{
    void Load() override 
    {
        if(_load_function)
            (*_load_function)(this);
        Instance::Load();
    }

    void Open() override
    {
        if(_open_function)
            (*_open_function)(this);
        Instance::Open();
    }

    void Update(float seconds_elapsed) override
    {   
        if(_update_function)
            (*_update_function)(this,seconds_elapsed);
        Instance::Update(seconds_elapsed);
    }

    void Close() override 
    {
        if(_close_function)
            (*_close_function)(this);
        Instance::End();
        //Launch Instance Ended event with information about what to do next
    }

    void Unload() override
    {
        if(_unload_function)
            (*_unload_function)(this);

        Instance::Unload();
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

    void LoadFromFile(const LuaRef& stage_table, std::string stage_name)
    {   
        if (luaL_dofile(lua_state, script_path.c_str()) == 0)
        {
            _instance_table = std::make_shared<LuaRef>(getGlobal(lua_state, entity_name.c_str()));
            if ((*_instance_table).isTable())
            {
                if ((*_instance_table)["tilemap"])
                {
                    std::string tile_map_name = (*_instance_table)["tilemap"].cast<std::string>();
                }

                if ((*_instance_table)["Open"])
                {
                    _open_function = (*_instance_table)["Open"];
                }

                if ((*_instance_table)["Unload"])
                {
                    _load_function = (*_instance_table)["Unload"];
                }

                if ((*_instance_table)["Load"])
                {
                    _unload_function = (*_instance_table)["Load"];
                }

                if ((*_instance_table)["Update"])
                {
                    _update_function = (*_instance_table)["Update"];
                }

                if ((*_instance_table)["Close"])
                {
                    _close_function = (*_instance_table)["Close"];
                }

                if ((*_instance_table)["OnEvent"])
                {
                    _on_event_function = (*_instance_table)["OnEvent"];
                }

                if ((*_instance_table)["GetSubscriptions"])
                {
                    _get_subscriptions_function = (*_instance_table)["GetSubscriptions"];
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