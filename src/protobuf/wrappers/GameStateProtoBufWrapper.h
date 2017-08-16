#ifndef GAMESTATEPROTOBUFWRAPPER_H
#define GAMESTATEPROTOBUFWRAPPER_H

#include <fstream>
#include "src/protobuf/cc/gamestate.pb.h"
#include "src/world/stage/Stage.h"
#include "src/game_objects/Entity.h"
#include "src/system/System.h"
#include "src/utils/lua/LuaUniversal.h"

/**
    Purpose: Wrapper for protocol buffer classes generated using the Google protocol buffer compiler. 
**/

class GameStateProtoBufWrapper
{
  public:
    template <typename T>
    void SetSystems(T &systems_list)
    {
        for (auto it = systems_list.begin(); it != systems_list.end(); it++)
        {
            pmidgserialized::System *system = serialized_game_state.add_active_systems();
            std::string name = (*it)->GetName();
            system->set_name(name);
        }
    }

    void SetEntities(const std::map<int, Entity *> &entities_list)
    {
        std::list<Entity *> entities;
        for (auto it = entities_list.begin(); it != entities_list.end(); it++)
        {
            entities.push_back(it->second);
        }

        SetEntities(entities);
    }
    
    template <typename T>
    void SetEntities(T &entities_list)
    {
        for (auto it = entities_list.begin(); it != entities_list.end(); it++)
        {
            Entity *e = *it;
            pmidgserialized::Entity *serialized_entity = serialized_game_state.add_entities();

            int id = e->ID();
            std::string name = e->GetPrototypeName();

            serialized_entity->set_id(id);
            serialized_entity->set_name(name);

            std::unordered_map<std::string, Component *> components = e->GetAllComponents();

            if (components.size() > 0)
            {

                for (auto it = components.begin(); it != components.end(); it++)
                {
                    pmidgserialized::Component *serialized_component = serialized_entity->add_components();
                    ConfigureSerializedComponent(serialized_component, it->second);
                }
            }
        }
    }

    void ConfigureSerializedComponent(pmidgserialized::Component* serialized_component, Component* component)
    {
        std::string name = component->GetName();
        serialized_component->set_name(name);

        std::unordered_map<std::string, Component::ComponentValue<float>> &float_values =
            component->GetAllFloatValues();

        std::unordered_map<std::string, Component::ComponentValue<std::string>> &string_values =
            component->GetAllStringValues();

        std::unordered_map<std::string, Component::ComponentValue<bool>> &bool_values =
            component->GetAllBoolValues();

        std::unordered_map<std::string, Component *> &sub_components =
            component->GetSubcomponents();

        for (auto it_vals = float_values.begin(); it_vals != float_values.end(); it_vals++)
        {
            pmidgserialized::ComponentValueFloat *serialized_component_value =
                serialized_component->add_float_values();

            ConfigureSerializedComponentValue<pmidgserialized::ComponentValueFloat, float>(it_vals->second, serialized_component_value);
        }

        for (auto it_vals = string_values.begin(); it_vals != string_values.end(); it_vals++)
        {
            pmidgserialized::ComponentValueString *serialized_component_value =
                serialized_component->add_string_values();
            ConfigureSerializedComponentValue<pmidgserialized::ComponentValueString, std::string>(it_vals->second, serialized_component_value);
        }

        for (auto it_vals = bool_values.begin(); it_vals != bool_values.end(); it_vals++)
        {
            pmidgserialized::ComponentValueBool *serialized_component_value =
                serialized_component->add_bool_values();

            ConfigureSerializedComponentValue<pmidgserialized::ComponentValueBool, bool>(it_vals->second, serialized_component_value);
        }

        for (auto it_vals = sub_components.begin(); it_vals != sub_components.end(); it_vals++)
        {
            pmidgserialized::Component* serialized_sub_component =
                serialized_component->add_subcomponents();
            ConfigureSerializedComponent(serialized_sub_component, it_vals->second);
        }
    }


    void SetStage(Stage& stage)
    {
        pmidgserialized::Stage* serialzied_stage = serialized_game_state.mutable_stage();
        
        LuaStage* lua_stage = dynamic_cast<LuaStage*>(&stage);
        std::string file = lua_stage->GetFile();
        std::string name = lua_stage->GetName();

        const std::unordered_map<int, std::string>& instances = lua_stage->GetInstanceNames();

        for(auto it = instances.begin(); it != instances.end(); it++)
        {
            int instance_id = it->first;
            serialzied_stage->add_instances(instance_id);
        }

        if(lua_stage->GetRootInstance())
            serialzied_stage->set_root_instance(lua_stage->GetRootInstance()->GetID());

        serialzied_stage->set_file(file);
        serialzied_stage->set_name(name);
    }

    template <typename T>
    void GetEntities(T &entities_list)
    {
        int num_of_entities = serialized_game_state.entities_size();

        // iterate over entities
        for (int i = 0; i < num_of_entities; i++)
        {
            pmidgserialized::Entity current_entity = serialized_game_state.entities(i);

            int entity_id = current_entity.id();
            std::string name = current_entity.name();

            Entity *e = new Entity(0, name, entity_id);

            int num_of_components = current_entity.components_size();
            // iterate over components
            for (int k = 0; k < num_of_components; k++)
            {
                pmidgserialized::Component current_component = current_entity.components(k);
                e->AddComponent(GenerateComponent(current_component));
            }
            entities_list.push_back(e);
        }
    }

    Component *GenerateComponent(pmidgserialized::Component component)
    {

        std::string component_name = component.name();
        Component *component_to_add = new Component(component_name);
        
        int num_of_bool_values = component.bool_values_size();
        int num_of_string_values = component.string_values_size();
        int num_of_float_values = component.float_values_size();
        int num_of_subcomponents = component.subcomponents_size();

        // iterate over component values
        for (int j = 0; j < num_of_bool_values; j++)
        {
            pmidgserialized::ComponentValueBool current_value =
                component.bool_values(j);
            ConfigureComponent<pmidgserialized::ComponentValueBool, bool>(component_to_add, current_value);
        }

        for (int j = 0; j < num_of_string_values; j++)
        {
            pmidgserialized::ComponentValueString current_value =
                component.string_values(j);
            ConfigureComponent<pmidgserialized::ComponentValueString, std::string>(component_to_add, current_value);
        }

        for (int j = 0; j < num_of_float_values; j++)
        {
            pmidgserialized::ComponentValueFloat current_value =
                component.float_values(j);
            ConfigureComponent<pmidgserialized::ComponentValueFloat, float>(component_to_add, current_value);
        }

        for (int j = 0; j < num_of_subcomponents; j++)
        {
            Component *sub = GenerateComponent(component.subcomponents(j));
            component_to_add->AddSubcomponent(sub);
        }

        return component_to_add;
    }

    //maybe have this return actual system objects?
    template <typename T>
    void GetSystems(T &systems)
    {
        //call system factory
        int num_of_systems = serialized_game_state.active_systems_size();

        for (int i = 0; i < num_of_systems; i++)
        {
            pmidgserialized::System current_system = serialized_game_state.active_systems(i);
            std::string system_name = current_system.name();
            systems.push_back(system_name);
        }
    }

    void GetStage(LuaStage* stage)
    {
        pmidgserialized::Stage serialized_stage = serialized_game_state.stage();

        if(stage)
            stage->LoadFromFile(LUA_STATE,serialized_stage.file(),serialized_stage.name());

        int num_of_instances = serialized_stage.instances_size();

        for(int i =0; i < num_of_instances; i++)
        {
            int instance_id = serialized_stage.instances(i);
            stage->AddInstance(instance_id);
        }

        if(serialized_stage.has_root_instance())
        {
            int root_instance_id = serialized_stage.root_instance();
            stage->SetRootInstance(root_instance_id);
        }
    }

    void FromFile(std::string file_name)
    {
        std::fstream input(file_name.c_str(), std::ios::in | std::ios::binary);
        serialized_game_state.ParseFromIstream(&input);
    }

    void ToFile(std::string file_name)
    {
        std::fstream output(file_name.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
        serialized_game_state.SerializeToOstream(&output);
    }

  private:
    template <typename ST, typename T>
    static void ConfigureComponent(Component *c, ST serialized_value)
    {
        std::string value_name = serialized_value.value_name();
        T value = serialized_value.value();
        c->AddValue(value_name, value);
    }

    template <typename ST, typename T>
    static void ConfigureSerializedComponentValue(Component::ComponentValue<T> &component_value, ST *serialized_component_value)
    {
        std::string component_value_name = component_value.GetName();
        T value = component_value.GetValue();
        serialized_component_value->set_value_name(component_value_name);
        serialized_component_value->set_value(value);
    }
    pmidgserialized::GameState serialized_game_state;
};
#endif