#include "src/protobuf/wrappers/GameStateProtoBufWrapper.h"

void GameStateProtoBufWrapper::SetEntities(const std::map<int, Entity *> &entities_list)
{
    std::list<Entity *> entities;
    for (auto it = entities_list.begin(); it != entities_list.end(); it++)
    {
        entities.push_back(it->second);
    }

    SetEntities(entities);
}

void GameStateProtoBufWrapper::ConfigureSerializedComponent(pmidgserialized::Component *serialized_component, Component *component)
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
        pmidgserialized::Component *serialized_sub_component =
            serialized_component->add_subcomponents();
        ConfigureSerializedComponent(serialized_sub_component, it_vals->second);
    }
}

void GameStateProtoBufWrapper::SetStage(Stage &stage)
{
    pmidgserialized::Stage *serialzied_stage = serialized_game_state.mutable_stage();

    LuaStage *lua_stage = dynamic_cast<LuaStage *>(&stage);
    std::string file = lua_stage->GetFile();
    std::string name = lua_stage->GetName();

    const std::unordered_map<int, std::string> &instances = lua_stage->GetInstanceNames();

    for (auto it = instances.begin(); it != instances.end(); it++)
    {
        int instance_id = it->first;
        serialzied_stage->add_instances(instance_id);
    }

    if (lua_stage->GetRootInstance())
        serialzied_stage->set_root_instance(lua_stage->GetRootInstance()->GetID());

    serialzied_stage->set_file(file);
    serialzied_stage->set_name(name);
}

Component *GameStateProtoBufWrapper::GenerateComponent(pmidgserialized::Component component)
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

void GameStateProtoBufWrapper::GetStage(LuaStage *stage)
{
    pmidgserialized::Stage serialized_stage = serialized_game_state.stage();

    if (stage)
        stage->LoadFromFile(LUA_STATE, serialized_stage.file(), serialized_stage.name());

    int num_of_instances = serialized_stage.instances_size();

    for (int i = 0; i < num_of_instances; i++)
    {
        int instance_id = serialized_stage.instances(i);
        stage->AddInstance(instance_id);
    }

    if (serialized_stage.has_root_instance())
    {
        int root_instance_id = serialized_stage.root_instance();
        stage->SetRootInstance(root_instance_id);
    }
}

void GameStateProtoBufWrapper::FromFile(std::string file_name)
{
    std::fstream input(file_name.c_str(), std::ios::in | std::ios::binary);
    serialized_game_state.ParseFromIstream(&input);
}

void GameStateProtoBufWrapper::ToFile(std::string file_name)
{
    std::fstream output(file_name.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
    serialized_game_state.SerializeToOstream(&output);
}