#ifndef LUASTAGE_H
#define LUASTAGE_H

class LuaStage : public Stage
{
    void Load(const LuaRef& stage_table, std::string stage_name)
    {

    }

    void Load() override 
    {

    }

    void Start() override
    {

    }

    void Update() override
    {

    }

    void End() override 
    {
        //Launch StageEnd event with information about what to do next
    }

    void OnEvent(Event& e) override
    {
        //Listen for stage end condition -owner of stage needs to listen for stage end requests
    }

    std::list<Subscription> GetSubscriptions() override
    {

    }

};

#endif