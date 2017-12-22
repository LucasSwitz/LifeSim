#ifndef MAINMENULISTENER_H
#define MAINMENULISTENER_H

class MainMenuListener
{
    public:
        virtual void LoadStagePressed(std::string& stage_name) = 0;
        virtual void SaveStagePressed(std::string& file_name) = 0;
        virtual void NewInstancePressed(std::string& instance_name) = 0;
        virtual void NewStagePressed() = 0;
        virtual void NewUIPressed() = 0;
        virtual void AttachUIPressed(std::string& ui_name) = 0;
        virtual void GameModePressed() = 0;
        virtual void UIModePressed() = 0;
};
#endif