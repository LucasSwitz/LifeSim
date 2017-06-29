#ifndef LOGGING
#define LOGGING

#define LOG Logging::Instance()

#include <string>
#include "src/gui/gui_tools/DevelopmentOverlay.h"
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
    
private: 

    void LogFile(std::string msg)
    {

    }

    void LogOverlay(const char* msg, va_list args)
    {
        DevelopmentOverlay::Instance()->GetLog().AddLog(msg, args);
    }

};
#endif
