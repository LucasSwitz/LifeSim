#ifndef DEVELOPMENTOVERLAYLISTENER_H
#define DEVELOPMENTOVERLAYLISTENER_H

#include <string>

class DevelopmentOverlayListener
{
  public:
    virtual void OnCreateBlankInstance(std::string& instance_name, int width, int height){};
    virtual void OnCreateBlankStage(){};
    virtual void OnLoadStageFile(const std::string &file_name){};
    virtual void OnSaveStageFile(const std::string &file_name){};
    virtual void OnLaunchInstance(){};
    virtual void OnLaunchStage(){};
    virtual void OnModeChangeGame(){};
    virtual void OnModeChangeUI(){};
    virtual void OnNewUI(){};
};

#endif