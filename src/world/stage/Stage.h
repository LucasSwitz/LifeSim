#ifndef STAGE_H
#define STAGE_H

#include <unordered_map>

class Stage : public EventListener
{
public:
    void ChangeCurrentInstance(Instance* instance)
    {
        _current_instance->Close();
        _current_instance = instance;

        if(!_current_instance->IsLoaded())
            _current_instance->Load();

        _current_instance->Open();
    }

    virtual void Update(float seconds_elapsed)
    {
        _current_instance->Update(seconds_elapsed);
    }

    //load first instance;
    virtual void Enter()
    {
        _root_instance->Load();
        _root_instance->Open();
    }

    virtual void AddInstance(int id, Instance * instance)
    {
        _instances.insert(std::make_pair{id,instance});
    }

    void SetRootInstance(Instance* instance)
    {
        _root_instance = instance;
    }

    bool HasInstance(int id)
    {
        return _instances.find(id) != instances.end();
    }

    //Unload all loaded instances
    virtual void Exit()
    {
        for(auto it = _instances.begin(); it != _instances.end(); it++)
        {
            Instance* inst = it->seconds;

            if(inst->IsOpen())
                inst->Close();
            if(inst->IsLoaded())
                inst->Unload();
        }

        if(_root_instance->IsOpen())
            _root_instance->Close();

        _root_instance->Unload();
    }

    virtual void OnEvent(Event& e)
    {
        if(e->EventType::CHANGE_INSTANCE_EVENT)
        {
            int instance_id = e->DereferenceToType<int>();
            ChangeInstance(_instances.at(instance_id));
        }
    }

    virtual std::list<Subscription> GetSubscriptions() //should really change this to pass lists by reference
    {

    }

private:
    std::unordered_map<int, Instance*> _instances;
    Instance* _current_instance;
    Instance* _root_instance;
};

#endif