#ifndef LOGGING_H
#define LOGGING_H

#define LOG Logging::Instance()

#include <string>
#include <iostream>
#include <stdarg.h>

class Logging{
    public:
        static const int FILE = 0;
        static const int DEV_LOG = 1;
    
    static Logging* Instance()
    {
        static Logging log;
        return &log;
    }

    void LogInfo(int channel,const char * msg, ... )
    {
        va_list args;
        va_start(args, msg);
        
        switch(channel)
        {
            case FILE:
                LogFile(msg);
                break;
            case DEV_LOG:
                LogOverlay(msg,args);
                break;
            default:
                break;
        }
    }

    void LogAll(std::string msg)
    {

    }

    void LogFile(std::string msg)
    {

    }

    void LogOverlay(const char* msg, va_list& args)
    {

    }

    void LogOverlay(const std::string& msg)
    {
        
    }

};
#endif
