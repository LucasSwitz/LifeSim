#ifndef GAMESTATEPROTOBUFWRAPPER_H
#define GAMESTATEPROTOBUFWRAPPER_H

#include <fstream>
#include "src/protobuf/cc/gamestate.pb.h"
#include "src/world/stage/LuaStage.h"
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

  template <typename T>
  void SetEntities(T &entities_list)
  {
    for (auto it = entities_list.begin(); it != entities_list.end(); it++)
    {
      Entity *e = *it;
      pmidgserialized::Entity *serialized_entity = serialized_game_state.add_entities();

      int id = e->ID();
      int instance = e->GetInstance();

      std::string name = e->GetPrototypeName();

      serialized_entity->set_id(id);
      serialized_entity->set_instance(instance);
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
      int instance = current_entity.instance();

      Entity *e = new Entity(0, name, entity_id);
      e->SetInstance(instance);

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

  void GetStage(LuaStage *stage);

  void FromFile(std::string file_name);

  void ToFile(std::string file_name);

  void SetEntities(const std::map<int, Entity *> &entities_list);
  
  void SetStage(Stage &stage);

  void ConfigureSerializedComponent(pmidgserialized::Component *serialized_component, Component *component);

  Component *GenerateComponent(pmidgserialized::Component component);

private:
  template <typename ST, typename T>
  void ConfigureComponent(Component *c, ST serialized_value)
  {
    std::string value_name = serialized_value.value_name();
    T value = serialized_value.value();
    c->AddValue(value_name, value);
  }

  template <typename ST, typename T>
  void ConfigureSerializedComponentValue(Component::ComponentValue<T> &component_value, ST *serialized_component_value)
  {
    std::string component_value_name = component_value.GetName();
    T value = component_value.GetValue();
    serialized_component_value->set_value_name(component_value_name);
    serialized_component_value->set_value(value);
  }

  pmidgserialized::GameState serialized_game_state;
};
#endif