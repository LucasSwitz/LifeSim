#ifndef STAGE_H
#define STAGE_H

#include <unordered_map>

class Stage : public EventListener
{

    void ChangeCurrentInstance(Instance* instance)
    {
        _current_instance->Close();
        _current_instance = instance;

        if(!_current_instance->IsLoaded())
            _current_instance->Load();

        _current_instance->Open();
    }

    void Update(double seconds_elapsed)
    {
        _current_instance->Update();
    }

    void Enter()
    {
        //load first instance;
    }

    void Exit()
    {
        //Unload all loaded instances
    }

    void OnEvent(Event& e)
    {
        if(e->EventType::CHANGE_INSTANCE_EVENT)
        {
            int instance_id = e->DereferenceToType<int>();
            ChangeInstance(_instances.at(instance_id));
        }
    }

    std::list<Subscription> GetSubscriptions() //should really change this to pass lists by reference
    {

    }

private:
    std::unordered_map<int, Instance*> _instances;

};

#endif