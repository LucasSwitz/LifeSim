#ifndef LUASTAGE_H
#define LUASTAGE_H

#include <memory>
#include "src/world/stage/Stage.h"
#include "src/utils/lua/LuaUniversal.h"
#include "src/world/stage/LuaInstanceFactory.h"

/**
    Purpose: Stage defined by a Lua file.
**/
class LuaStage : public Stage
{
    public:

    void Enter() override
    {
        if(_enter_function)
            (*_enter_function)(this);

        Stage::Enter();
    }

    void Tick(float seconds_elapsed) override
    {   
        if(_update_function)
            (*_update_function)(this);

        Stage::Tick(seconds_elapsed);
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
        std::list<Subscription> subs = Stage::GetSubscriptions();

        if(_get_subscriptions_function)
        {
            LuaRef lua_subs = (*_get_subscriptions_function)(this);
            std::list<Subscription> lua_subs_list;
            LuaUniversal::ListFromTable<Subscription>(lua_subs, lua_subs_list);
            subs.splice(std::end(subs), lua_subs_list);
        }

        return subs;
    }

    void LoadFromFile(lua_State* lua_state, const std::string script_path, const std::string& stage_name)
    {
        _file = script_path;
         if (luaL_dofile(lua_state, script_path.c_str()) == 0)
        {
            LuaRef stage_table = getGlobal(lua_state, stage_name.c_str());
            if ((stage_table).isTable())
            {
                if((stage_table)["root"])
                {
                    std::string root_instance_name = (stage_table)["root"].cast<std::string>(); 
                    _root_instance = ptr<Instance>
                        (LuaInstanceFactory::Inst()->GetInstance(root_instance_name));   
                }
                if((stage_table)["Instances"])
                {
                    LoadInstancesFromRef((stage_table)["Instances"]);
                }

                if ((stage_table)["Enter"])
                {
                    _enter_function = std::make_unique<LuaRef>((stage_table)["Enter"]);
                }

                if ((stage_table)["Update"])
                {
                    _update_function = std::make_unique<LuaRef>((stage_table)["Update"]);
                }

                if ((stage_table)["Exit"])
                {
                    _exit_function = std::make_unique<LuaRef>((stage_table)["Exit"]);
                }

                if ((stage_table)["OnEvent"])
                {
                    _on_event_function = std::make_unique<LuaRef>((stage_table)["OnEvent"]);
                }

                if ((stage_table)["GetSubscription"])
                {
                    _get_subscriptions_function = std::make_unique<LuaRef>((stage_table)["GetSubscriptions"]);
                }
            }
        }
        else
        {
            std::cout << "Error, can't open script: " << script_path << std::endl;
        }
    }

    std::string GetFile()
    {
        return _file;
    }

    private:

        void LoadInstancesFromRef(const LuaRef& instance_table)
        {
            Instance* new_instance = nullptr;
            std::unordered_map<std::string, LuaRef> vals = LuaUniversal::KeyValueMapFromTable(instance_table);

            for(auto it = vals.begin(); it != vals.end(); it++)
            {
                if((it->second).isNumber())
                {
                    int id = it->second.cast<int>();
                    new_instance = LuaInstanceFactory::Inst()->GetInstance(id);
                } 
                else if((it->second).isString())
                {
                    std::string name = it->second.cast<std::string>();
                    new_instance = LuaInstanceFactory::Inst()->GetInstance(name);
                }
                else
                {
                    //not valid Instance identifier
                }
            }

            if(new_instance)
                AddInstance(ptr<Instance>(new_instance));
        }

        void LoadRootInstanceFromRef(const LuaRef& root)
        {
            Instance* root_instance = nullptr;
            if(root.isString())
            {
                int id = root.cast<int>();
                root_instance = LuaInstanceFactory::Inst()->GetInstance(id);
            }
            else if(root.isNumber())
            {   
                std::string name = root.cast<std::string>();
                root_instance = LuaInstanceFactory::Inst()->GetInstance(name);
            }
            else
            {
                //invalid instance identifiyer
            }

            if(root_instance)
                SetRootInstance(ptr<Instance>(root_instance));
        }   

        std::unique_ptr<LuaRef> _enter_function;
        std::unique_ptr<LuaRef> _update_function;
        std::unique_ptr<LuaRef> _exit_function;
        std::unique_ptr<LuaRef> _on_event_function;
        std::unique_ptr<LuaRef> _get_subscriptions_function;

        std::string _file = "";

};

#endif