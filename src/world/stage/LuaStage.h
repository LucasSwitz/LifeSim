#ifndef LUASTAGE_H
#define LUASTAGE_H

#include "src/world/Stage.h"

class LuaStage : public Stage
{
    public:
    void Enter() override
    {
        if(_enter_function)
            (*_enter_function)(this);
        Stage::Enter();
    }

    void Update(float seconds_elapsed) override
    {   
        if(_update_function)
            (*_update_function)(this);
        Stage::Update(seconds_elapsed);
    }

    void Exit() override
    {
        if(_exit_function)
            (*_exit_function)(this);
        Stage::Exit();
    }

    void OnEvent(Event& e) override
    {
        if(_on_event_function)
            (*_on_event_function)(this);
        Stage::OnEvent(e);
    }

    std::list<Subscription> GetSubscriptions() override
    {
        if(_get_subscriptions_function)
            (*_get_subscriptions_function)(this);
        
        Stage::GetSubscriptions();
    }

    void LoadFromFile(const LuaRef& stage_table, const std::string& stage_name)
    {
         if (luaL_dofile(lua_state, script_path.c_str()) == 0)
        {
            _stage_table = std::make_shared<LuaRef>(getGlobal(lua_state, entity_name.c_str()));
            if ((*_stage_table).isTable())
            {
                if ((*_stage_table)["Enter"])
                {
                    _enter_function = (*_stage_table)["Enter"];
                }

                if ((*_stage_table)["Update"])
                {
                    _open_function = (*_stage_table)["Open"];
                }

                if ((*_stage_table)["Exit"])
                {
                    _load_function = (*_stage_table)["Unload"];
                }
                if ((*_stage_table)["OnEvent"])
                {
                    _on_event_function = (*_stage_table)["OnEvent"];
                }
                if ((*_stage_table)["GetSubscription"])
                {
                    _get_subscriptions_function = (*_stage_table)["GetSubscriptions"];
                }


            }
        }
        else
        {
            std::cout << "Error, can't open script: " << script_path << std::endl;
        }        
    }

    private:
        std::unique_ptr<LuaRef> _enter_function;
        std::unique_ptr<LuaRef> _update_function;
        std::unique_ptr<LuaRef> _exit_function;
        std::unique_ptr<LuaRef> _on_event_function;
        std::unique_ptr<LuaRef> _get_subscriptions_function;

};

#endif