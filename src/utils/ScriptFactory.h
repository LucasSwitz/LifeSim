#ifndef SCRIPTFACTORY_H
#define SCRIPTFACTORY_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <experimental/filesystem>
#include <algorithm>

#define PREAMBLE_START "PREAMBLE_START"
#define PREAMBLE_END "PREAMBLE_END"

using namespace std::experimental::filesystem;
template <typename T>
class ScriptFactory
{
  public:
    ScriptFactory(std::string search_directory, std::string script_type, bool configurable = false) : _search_directory(search_directory), 
    _script_type(script_type), _configurable(configurable) {}

    struct Preamble
    {
        bool IsValid()
        {

            return !preamble_flags.empty() && HasFlag("ScriptType");
        }

        std::string GetFlag(std::string flag_name)
        {
            return preamble_flags.at(flag_name);
        }
        
        bool HasFlag(std::string flag_name)
        {
            return preamble_flags.find("Name") != preamble_flags.end();
        }

        static Preamble FromStream(std::ifstream &stream)
        {
            Preamble pre;

            //get preamble lines

            std::string line = "";
            
            //this is inefficient. Find a better way so you're no skipping first iteration.


            std::getline(stream, line);

            //make sure this file has a preamble
            if(line.find(PREAMBLE_START) == std::string::npos)
            {
                return pre;
            }
            
            while (line.find(PREAMBLE_END) == std::string::npos)
            {

                std::string value = "";
                std::string key = "";

                if (line.find("=") != std::string::npos)
                {
                    value = line.substr(line.find("=") + 1);
                    key = line.substr(0, line.find("=") - 1);

                    value.erase(remove_if(value.begin(), value.end(), isspace), value.end());
                    value.erase(std::remove(value.begin(), value.end(), '"'), value.end());

                    pre.preamble_flags.insert(std::make_pair(key,value));
                }

                std::getline(stream, line);
            }


            return pre;
        }

        bool IsType(std::string desired_type)
        {
            return GetFlag("ScriptType").compare(desired_type) == 0;
        }

        std::unordered_map<std::string, std::string> preamble_flags;
    };

    void PopulateFactory(std::string search_directory = "")
    {
        if (search_directory.empty())
            search_directory = _search_directory;

        for (auto &full_file_path : directory_iterator(search_directory))
        {
            path current_path = full_file_path.path();

            if (is_regular_file(current_path))
            {

                std::string current_path_string = current_path.string();
                std::ifstream file_read_stream(current_path_string);

                if (file_read_stream.good())
                {
                    Preamble preamble = Preamble::FromStream(file_read_stream);
                    if (preamble.IsValid() && preamble.IsType(_script_type))
                    {

                        //std::cout << "Adding Script: " << preamble.GetFlag("Name") << std::endl;
                        if(_configurable)
                        { 
                            AddScript(preamble, Configure(current_path_string, preamble.GetFlag("Name")));
                        }
                        else
                        {
                            AddScript(preamble, current_path_string);
                        }
                    }
                    else
                    {
                        //std::cout << "Bad Preamble: " << current_path_string << std::endl;
                    }
                }
                else
                {
                    //std::cout << "Bad ifStream" << std::endl;
                }
            }
            else
            {
                PopulateFactory(current_path);
            }
        }
    }

  protected:
    virtual T *Configure(std::string script_path, std::string scriptable_name){};

    virtual void AddScript(Preamble &pre, T *scriptable_object){};
    virtual void AddScript(Preamble &pre, std::string script_path){};


  private:
    std::string _search_directory;
    std::string _script_type;
    bool _configurable;
};

#endif