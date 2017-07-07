#ifndef LUASTAGE_H
#define LUASTAGE_H

class LuaInstance : public Instance
{
    void Load(const LuaRef& stage_table, std::string stage_name)
    {

    }

    void Load() override 
    {
        Instance::Load();
    }

    void Open() override
    {
        Instance::Open();
    }

    void Update() override
    {
        Instance::Update(seconds_elapsed);
    }

    void End() override 
    {
        Instance::End()
        //Launch Instance Ended event with information about what to do next
    }

    void OnEvent(Event& e) override
    {
        //Listen for stage end condition -owner of stage needs to listen for stage end requests
        Instance::OnEvent(e);
    }

    std::list<Subscription> GetSubscriptions() override
    {

    }

};

#endif