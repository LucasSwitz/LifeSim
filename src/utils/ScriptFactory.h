#include <string>
#include <unordered_map>
#include <fstream>
#include <experimental/filesystem>

#define PREAMBLE_LINES 3

using namespace std::experimental::filesystem;
template <typename T>
class ScriptFactory
{
  public:
    ScriptFactory(std::string search_directory, std::string script_type) : _search_directory(search_directory), _script_type(script_type) {}

    struct Preamble
    {
        bool IsValid()
        {
            return !type.empty() && !owner.empty() && !name.empty();
        }

        static Preamble FromStream(std::ifstream &stream)
        {
            Preamble pre;

            std::getline(stream, pre.type);
            std::getline(stream, pre.owner);
            std::getline(stream, pre.name);

            if (pre.type.find("=") != std::string::npos)
                pre.type = pre.type.substr(pre.type.find("=") + 1);
            if (pre.owner.find("=") != std::string::npos)
                pre.owner = pre.owner.substr(pre.owner.find("=") + 1);
            if (pre.name.find("=") != std::string::npos)
                pre.name = pre.name.substr(pre.name.find("=") + 1);

            pre.type.erase(remove_if(pre.type.begin(), pre.type.end(), isspace), pre.type.end());
            pre.owner.erase(remove_if(pre.owner.begin(), pre.owner.end(), isspace), pre.owner.end());
            pre.name.erase(remove_if(pre.name.begin(), pre.name.end(), isspace), pre.name.end());

            pre.type.erase(std::remove( pre.type.begin(),  pre.type.end(), '"'),  pre.type.end());
            pre.owner.erase(std::remove(pre.owner.begin(), pre.owner.end(), '"'), pre.owner.end());
            pre.name.erase(std::remove(pre.name.begin(), pre.name.end(), '"'), pre.name.end());

            return pre;
        }

        bool IsType(std::string desired_type)
        {
            return (type.compare(desired_type) == 0);
        }

        std::string type;
        std::string owner;
        std::string name;
    };

    void PopulateFactory(std::string search_directory="")
    {
        if(search_directory.empty())
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
                    if (preamble.IsType(_script_type) && preamble.IsValid())
                    {
                        //TODO: Log this std::cout << "Adding Script: " << preamble.name << std::endl;
                        AddScript(preamble.owner, preamble.name, Configure(current_path_string, preamble.name));
                    }
                    else
                    {
                        //TODO: Log this std::cout << "Bad Preamble: " << current_path_string << std::endl;
                    }
                }
                else
                {
                    //TODO: Log this std::cout << "Bad ifStream" << std::endl;
                }
            }
            else{
                PopulateFactory(current_path);
            }
        }
    }

  protected:
    virtual T *Configure(std::string script_path, std::string script_name) = 0;

    void AddScript(std::string script_owner, std::string script_name, T *scriptable_object)
    {
        auto it = _scripts_map.find(script_owner);
        if (it == _scripts_map.end())
        {
            std::unordered_map<std::string, ScriptableState *> class_states;
            class_states.insert(std::make_pair(script_name, scriptable_object));

            _scripts_map.insert(std::make_pair(script_owner, class_states));
        }
        else
        {
            it->second.insert(std::make_pair(script_name, scriptable_object));
        }
    }

  protected:
    std::unordered_map<std::string, std::unordered_map<std::string, T *>> _scripts_map;

  private:
    std::string _search_directory;
    std::string _script_type;
};