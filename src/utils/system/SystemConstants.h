#ifndef SYSTEMCONSTANTS_H
#define SYSTEMCONSTANTS_H

#define SystemC SystemConstants::Instance();

#include <srtring.>

class SystemConstants
{
    public: 
        void Load();

        static SystemConstants* Instance()
        {
            static SystemConstants instance;
            return &instance;
        }
        
        template<typename T>
        T Get(std::string value);
}