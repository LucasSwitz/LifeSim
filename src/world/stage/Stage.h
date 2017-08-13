#ifndef STAGE_H
#define STAGE_H

#include <unordered_map>
#include "src/world/stage/Instance.h"
#include "src/event/EventSubscriber.h"
#include "src/event/EventType.h"
#include "src/game/FPSRunnable.h"

/**
    Purpose: Stages are purely logical containers for handling asset loading,
    active instances, and transitioning to other stages. When a stage is loaded, it will
    load all graphics asset required by the root instance. Every stage can have multiple
    instances, but will only ever have one active instance (the instance that is rendered and
    players can interact with).
**/

class Stage : public EventSubscriber, public FPSRunnable
{
  public:
    void Load() override
    {
    }

    void Unload() override
    {
        
    }

    virtual void Tick(float seconds_elapsed) override
    {
        if(_current_instance)
            _current_instance->Tick(seconds_elapsed);
    }

    //load first instance;
    virtual void Enter()
    {
        if (_root_instance)
        {
            _root_instance->Load();
            _root_instance->Open();
        }
        else
        {
            //error, no root instance specified
        }
    }
    //Unload all loaded instances
    virtual void Exit()
    {
        for (auto it = _instances.begin(); it != _instances.end(); it++)
        {
            Instance *inst = it->second;

            if (inst->IsOpen())
                inst->Close();
            if (inst->IsLoaded())
                inst->Unload();
        }

        if (_root_instance)
        {
            if (_root_instance->IsOpen())
                _root_instance->Close();

            _root_instance->Unload();
        }
    }

    void AddInstance(Instance *instance)
    {
        _instances.insert(std::make_pair(instance->GetID(), instance));
    }

    void SetRootInstance(Instance *instance)
    {
        _root_instance = instance;
    }

    void SetCurrentInstance(int id, bool do_load = true)
    {
        if(!HasInstance(id))
            return;

        _current_instance = GetInstance(id);

        if (do_load && !_current_instance->IsLoaded())
            _current_instance->Load();

        _current_instance->Open();
    }
    
    void ChangeInstance(int id)
    {
        if(!HasInstance(id))
            return;

        if (_current_instance)
            _current_instance->Close();

        SetCurrentInstance(id);
    }
    
    bool HasInstance(int id)
    {
        return _instances.find(id) != _instances.end();
    }

    Instance* GetCurrentInstance()
    {
        return _current_instance;
    }

    Instance* GetInstance(int id)
    {
        if(!HasInstance(id))
            return nullptr;
        else
        {
            return _instances.at(id);
        }
    }

    virtual void OnEvent(Event &e)
    {
        if (e.id == EventType::CHANGE_INSTANCE_EVENT)
        {
            int instance_id = *(e.InfoToType<int *>());
            ChangeInstance(instance_id);
        }
    }

    virtual std::list<Subscription> GetSubscriptions()
    {
        std::list<Subscription> subs = {Subscription(EventType::CHANGE_INSTANCE_EVENT)};
        return subs;
    }

    std::string GetName()
    {
        return _name;
    }

    void SetName(std::string name)
    {
        _name = name;
    }

    const std::unordered_map<int, Instance*> GetInstances() const
    {
        return _instances;
    } 

  protected:
    Instance *_current_instance = nullptr;
    Instance *_root_instance = nullptr;

  private:
    std::unordered_map<int, Instance *> _instances;
    std::string _name;
};

#endif