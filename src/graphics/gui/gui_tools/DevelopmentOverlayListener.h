#ifndef DEVELOPMENTOVERLAYLISTENER_H
#define DEVELOPMENTOVERLAYLISTENER_H

#include <string>

class DevelopmentOverlayListener
{
    public:
        virtual void OnCreateBlankInstance(int width, int height) = 0;
        virtual void OnLoadGameStateFile(const std::string& file_name) = 0;
        virtual void OnSaveGameStateFile(const std::string& file_name) = 0;
};

#endif