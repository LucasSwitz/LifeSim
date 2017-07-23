#ifndef GAMESTATEPROTOBUFWRAPPER_H
#define GAMESTATEPROTOBUFWRAPPER_H

#include <fstream>
#include "src/protobuf/cc/gamestate.pb.h"
#include "src/world/stage/Instance.h"
#include "src/game_objects/Entity.h"
#include "src/system/System.h"

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


    void SetEntities(std::map<int, Entity*> &entities_list)
    {   
        std::list<Entity*> entities;
        for(auto it = entities_list.begin(); it != entities_list.end(); it++)
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
            serialized_entity->set_id(id);

            auto components = e->GetAllComponents();

            if (components.size() > 0)
            {
                pmidgserialized::Component *serialized_component = serialized_entity->add_components();

                for (auto it = components.begin(); it != components.end(); it++)
                {
                    Component *component = it->second;
                    std::string name = component->GetName();
                    serialized_component->set_name(name);

                    auto float_values = component->GetAllFloatValues();
                    auto string_values = component->GetAllStringValues();
                    auto bool_values = component->GetAllBoolValues();

                    for (auto it = float_values.begin(); it != float_values.end(); it++)
                    {
                        pmidgserialized::ComponentValueFloat *serialized_component_value =
                            serialized_component->add_float_values();

                        ConfigureSerializedComponentUser<pmidgserialized::ComponentValueFloat, float>(it->second, serialized_component_value);
                    }

                    for (auto it = string_values.begin(); it != string_values.end(); it++)
                    {
                        pmidgserialized::ComponentValueString *serialized_component_value =
                            serialized_component->add_string_values();

                        ConfigureSerializedComponentUser<pmidgserialized::ComponentValueString, std::string>(it->second, serialized_component_value);
                    }

                    for (auto it = bool_values.begin(); it != bool_values.end(); it++)
                    {
                        pmidgserialized::ComponentValueBool *serialized_component_value =
                            serialized_component->add_bool_values();

                        ConfigureSerializedComponentUser<pmidgserialized::ComponentValueBool, bool>(it->second, serialized_component_value);
                    }
                }
            }
        }
    }

    void SetInstance(Instance &instance)
    {
        pmidgserialized::Instance *serialized_instance = serialized_game_state.mutable_instance();

        std::string tile_map_file = instance.GetTileMap().GetFile();
        serialized_instance->set_tilemap(tile_map_file);
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

            Entity *e = new Entity(0,"",true, entity_id);

            int num_of_components = current_entity.components_size();

            // iterate over components
            for (int k = 0; k < num_of_components; k++)
            {
                pmidgserialized::Component current_component = current_entity.components(k);

                std::string current_component_name = current_component.name();

                int num_of_bool_values = current_component.bool_values_size();
                int num_of_string_values = current_component.string_values_size();
                int num_of_float_values = current_component.float_values_size();

                // iterate over component values
                for (int j = 0; j < num_of_bool_values; j++)
                {
                    pmidgserialized::ComponentValueBool current_value =
                        current_component.bool_values(j);
                    ConfigureComponentUser<pmidgserialized::ComponentValueBool, bool>(e, current_component_name, current_value);
                }

                for (int j = 0; j < num_of_bool_values; j++)
                {
                    pmidgserialized::ComponentValueString current_value =
                        current_component.string_values(j);
                    ConfigureComponentUser<pmidgserialized::ComponentValueString, std::string>(e, current_component_name, current_value);
                }

                for (int j = 0; j < num_of_float_values; j++)
                {
                    pmidgserialized::ComponentValueFloat current_value =
                        current_component.float_values(j);
                    ConfigureComponentUser<pmidgserialized::ComponentValueFloat, float>(e, current_component_name, current_value);
                }
            }
            entities_list.push_back(e);
        }
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

    void GetInstance(Instance* instance)
    {
        //create instance and call tilemap factor
        std::string tile_map_file = serialized_game_state.instance().tilemap();
        instance->GetTileMap().LoadFromFile(tile_map_file);
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
    static void ConfigureComponentUser(ComponentUser *user, std::string component_name, ST serialized_value)
    {
        std::string value_name = serialized_value.value_name();
        T value = serialized_value.value();

        user->AddComponentValue(component_name, value_name, value);
    }

    template <typename ST, typename T>
    static void ConfigureSerializedComponentUser(Component::ComponentValue<T> &component_value, ST *serialized_component_value)
    {
        std::string component_value_name = component_value.GetName();
        T value = component_value.GetValue();

        serialized_component_value->set_value_name(component_value_name);
        serialized_component_value->set_value(value);
    }

    pmidgserialized::GameState serialized_game_state;
};
#endif