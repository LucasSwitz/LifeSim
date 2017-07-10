#ifndef STAGE_H
#define STAGE_H

#include <unordered_map>
#include "src/world/stage/Instance.h"
#include "src/event/EventSubscriber.h"
#include "src/event/EventType.h"


//requires a loading screen to tranistion

class Stage : public EventSubscriber
{
public:
    void ChangeInstance(Instance* instance)
    {
        if(_current_instance)
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
        if(_root_instance)
        {
            _root_instance->Load();
            _root_instance->Open();
        }
        else
        {
            //error, no root instance specified
        }
            
    }


    bool HasInstance(int id)
    {
        return _instances.find(id) != _instances.end();
    }

    //Unload all loaded instances
    virtual void Exit()
    {
        for(auto it = _instances.begin(); it != _instances.end(); it++)
        {
            Instance* inst = it->second;

            if(inst->IsOpen())
                inst->Close();
            if(inst->IsLoaded())
                inst->Unload();
        }

        if(_root_instance)
        {
            if(_root_instance->IsOpen())
                _root_instance->Close();

            
            _root_instance->Unload();
        }
    }

    Instance* GetCurrentInstance()
    {
        return _current_instance;
    }

    virtual void OnEvent(Event& e)
    {
        if(e.id == EventType::CHANGE_INSTANCE_EVENT)
        {
            int instance_id = e.DereferenceInfoToType<int>();
            ChangeInstance(_instances.at(instance_id));
        }
    }

    virtual std::list<Subscription> GetSubscriptions() //should really change this to pass lists by reference
    {
        std::list<Subscription> subs = {Subscription(EventType::CHANGE_INSTANCE_EVENT)};
        return subs;
    }

protected:
    void AddInstance(Instance* instance)
    {
        _instances.insert(std::make_pair(instance->GetID(),instance));
    }

    void SetRootInstance(Instance* instance)
    {
        _root_instance = instance;
    }

protected:
    Instance* _current_instance = nullptr;
    Instance* _root_instance = nullptr;
private:
    std::unordered_map<int, Instance*> _instances;
};

#endif