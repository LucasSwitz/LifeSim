#ifndef DEVELOPMENTOVERLAYLISTENER_H
#define DEVELOPMENTOVERLAYLISTENER_H

#include <string>

class DevelopmentOverlayListener
{
  public:
    virtual void OnCreateBlankInstance(int width, int height){};
    virtual void OnCreateBlankStage(){};
    virtual void OnLoadStageFile(const std::string &file_name){};
    virtual void OnSaveStageFile(const std::string &file_name){};
    virtual void OnLaunchGameRunner(){};
    virtual void OnStopGameRunner(){};
};

#endif