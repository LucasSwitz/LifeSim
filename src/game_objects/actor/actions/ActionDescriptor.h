#ifndef ACTIONDESCRIPTOR_H
#define ACTIONDESCRIPTOR_H

#include <unordered_map>
#include <sstream>

struct ActionDescriptor
{
    std::string action;
    std::unordered_map<std::string, std::string> flags;

    ActionDescriptor(std::string command)
    {
        //parse it!
        std::stringstream ss(command);

        //pull out action
        ss >> action;

        //make action uppercase
        for (auto & c: action) c = toupper(c);

        std::string input = "";
        std::string last_flag = "";

        //pare flags
        while(ss >> input)
        {
            if(input.at(0) == '-' && last_flag.empty())
            {
                last_flag = input.substr(1,input.length());
            }
            else
            {
                if(flags.find(last_flag) != flags.end())
                {
                    //TODO: Throw exception
                }
                else
                {
                    flags.insert(std::make_pair(last_flag,input));
                last_flag = "";
                }
            }
            input = "";
        }
    }
};

#endif