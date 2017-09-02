#ifndef MAINMENULISTENER_H
#define MAINMENULISTENER_H

class MainMenuListener
{
    public:
        virtual void LoadStagePressed(std::string& stage_name) = 0;
        virtual void SaveStagePressed(std::string& file_name) = 0;
        virtual void NewInstancePressed(std::string& instance_name) = 0;
        virtual void NewStagePressed() = 0;
};
#endif