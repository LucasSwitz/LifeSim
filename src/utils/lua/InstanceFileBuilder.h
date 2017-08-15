#ifndef INSTANCEFILEBUILDER_H
#define INSTANCEFILEBUILDER_H

#include <fstream>
#include "src/utils/lua/file_building/LuaFileTable.h"

class InstanceFileBuilder
{
  public:
    InstanceFileBuilder(std::string& instance_name, int& instance_id) : _name(instance_name), _id(instance_id)
    {
        instance_table = new LuaFileTable(instance_name);
    }

    void SetTilemapFile(std::string &file_path)
    {
        instance_table->add_primitive_field(new LuaFileFieldString("tile_map", file_path));
    }

    bool Output(std::string &file_path)
    {
        file_path+=".lua";
        GenerateFunctions();
        std::string output = instance_table->pack();
        GeneratePreamble(output);
        std::ofstream out(file_path.c_str());
        out << output;
        out.close();
    }

    void SetID(int id)
    {

    }

  private:

    void GeneratePreamble(std::string& output)
    {
        std::string pre = "--PREAMBLE_START \n";
        pre+= "ScriptType = \"Instance\" \n";
        pre+= "Name = \"" + _name + "\" \n";
        pre+= "ID = " + std::to_string(_id) + "\n";
        pre+= "--PREAMBLE_END";
        pre += "\n\n";
    
        output = pre+output;
    }

    void GenerateFunctions()
    {
        instance_table->add_function("Load")
            .add_param("instance")
            .end_function()
            .add_function("Open")
            .add_param("instance")
            .end_function()
            .add_function("Update")
            .add_param("instance")
            .add_param("seconds_elapsed")
            .end_function()
            .add_function("Close")
            .add_param("instance")
            .end_function()
            .add_function("Unload")
            .add_param("instance")
            .end_function()
            .add_function("OnEvent")
            .add_param("instance")
            .add_param("event")
            .end_function()
            .add_function("GetSubscriptions")
            .add_param("instance")
            .end_function();
    }
    LuaFileTable *instance_table = nullptr;
    std::string _name;
    int _id;
};
#endif