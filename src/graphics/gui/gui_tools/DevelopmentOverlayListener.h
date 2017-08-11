#ifndef DEVELOPMENTOVERLAYLISTENER_H
#define DEVELOPMENTOVERLAYLISTENER_H

#include <string>

class DevelopmentOverlayListener
{
  public:
    virtual void OnCreateBlankInstance(int width, int height){};
    virtual void OnLoadGameStateFile(const std::string &file_name){};
    virtual void OnSaveGameStateFile(const std::string &file_name){};
    virtual void OnLaunchGameRunner(){};
    virtual void OnStopGameRunner(){};
};

#endif