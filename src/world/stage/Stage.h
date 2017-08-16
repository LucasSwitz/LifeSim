#ifndef STAGE_H
#define STAGE_H

#include <unordered_map>
#include "src/world/stage/Instance.h"
#include "src/event/EventSubscriber.h"
#include "src/event/EventType.h"
#include "src/game/FPSRunnable.h"
#include "src/world/stage/LuaInstanceFactory.h"

/**
    Purpose: Stages are purely logical containers for handling asset loading,
    active instances, and transitioning to other stages. When a stage is loaded, it will
    load all graphics asset requgired by the root instance. Every stage can have multiple
    instances, but will only ever have one active instance (the instance that is rendered and
    players can interact with).
**/

class Stage : public EventSubscriber, public FPSRunnable
{
  public:
    void Load() override
    {
        MessageDispatch::Instance()->RegisterSubscriber(this);
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
        for (auto it = _instances_names.begin(); it != _instances_names.end(); it++)
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
        _instances_names.insert(std::make_pair(instance->GetName(), instance));
        _instances_id_to_name.insert(std::make_pair(instance->GetID(),instance->GetName()));
    }

    void AddInstance(int id)
    {
        AddInstance(LuaInstanceFactory::Inst()->GetInstance(id));
    }

    void AddInstance(std::string name)
    {
        AddInstance(LuaInstanceFactory::Inst()->GetInstance(name));
    }

    void SetRootInstance(Instance *instance)
    {
        _root_instance = instance;
    }

    void SetRootInstance(int id)
    {
        SetRootInstance(LuaInstanceFactory::Inst()->GetInstance(id));
    }

    void SetCurrentInstance(std::string name, bool do_load = true)
    {
        if(!HasInstance(name))
            return;

        _current_instance = GetInstance(name);

        if (do_load && !_current_instance->IsLoaded())
            _current_instance->Load();

        _current_instance->Open();
    }

    void SetCurrentInstance(int id, bool do_load = false)
    {
        SetCurrentInstance(GetName(id),do_load);
    }
    
    void ChangeInstance(const std::string& name)
    {
        if(!HasInstance(name))
            return;

        if (_current_instance)
            _current_instance->Close();

        SetCurrentInstance(name);
    }

    void ChangeInstance(int id)
    {
        ChangeInstance(GetName(id));
    }
    
    
    bool HasInstance(const std::string& name)
    {
        return _instances_names.find(name) != _instances_names.end();
    }

    bool HasInstance(int id)
    {
        return HasInstance(GetName(id));
    }

    std::string GetName(int id)
    {
        if(HasName(id))
            return _instances_id_to_name.at(id);
        return "";
    }

    bool HasName(int id)
    {
        return _instances_id_to_name.find(id) != _instances_id_to_name.end();
    }

    Instance* GetCurrentInstance()
    {
        return _current_instance;
    }

    Instance* GetInstance(const std::string& name)
    {
        if(!HasInstance(name))
            return nullptr;
        else
        {
            return _instances_names.at(name);
        }
    }

    Instance* GetInstance(const int id)
    {
        return GetInstance(GetName(id));
    }

    virtual void OnEvent(Event &e)
    {
        if (e.id == EventType::CHANGE_INSTANCE_EVENT)
        {
            int instance_id = *(e.InfoToType<int *>());
            ChangeInstance(instance_id);
        } 
        else if (e.id == EventType::ENTITY_SPAWNED_EVENT)
        {
            Entity* entity = e.InfoToType<Entity*>();
            int instance_id = e.target_id;
            Instance* instance = GetInstance(instance_id);
            instance->AddLocalEntity(entity->ID());
        }
    }

    virtual std::list<Subscription> GetSubscriptions()
    {
        std::list<Subscription> subs = {Subscription(EventType::CHANGE_INSTANCE_EVENT),
                                        Subscription(EventType::ENTITY_SPAWNED_EVENT)
                                        };
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

    const std::unordered_map<std::string, Instance*>& GetInstances() const
    {
        return _instances_names;
    } 

    const std::unordered_map<int, std::string>& GetInstanceNames() const
    {
        return _instances_id_to_name;
    }

    Instance* GetRootInstance()
    {
        return _root_instance;
    }

  protected:
    Instance *_current_instance = nullptr;
    Instance *_root_instance = nullptr;

  private:
    std::unordered_map<int, std::string> _instances_id_to_name;
    std::unordered_map<std::string, Instance *> _instances_names;
    std::string _name;
};

#endif