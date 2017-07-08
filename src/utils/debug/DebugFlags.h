#ifndef DEBUGFLAGS_H
#define DEBUGFLAGS_H

#include <unordered_map>

class DebugFlags
{
 public:
    void Clear()
    {
        flags.clear();
    }

    void Set(std::string key, std::string value)
    {
        if(HasFlag(key))
        {
            flags.find(key)->second = value;
        }
        else
        {
            flags.insert(std::make_pair(key,value));
        }
    }

    std::string Get(std::string key)
    {
        if(HasFlag(key))
        {
            return flags.at(key);
        }

        return "FLAG NOT FOUND";
    }

    bool HasFlag(std::string key)
    {
        return flags.find(key) != flags.end();
    }

    static DebugFlags* Instance()
    {
        static DebugFlags instance;
        return &instance;    
    }

    private:
        DebugFlags(){};
        std::unordered_map<std::string,std::string> flags;
};


#endif