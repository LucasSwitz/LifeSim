#ifndef MAINMENULISTENER_H
#define MAINMENULISTENER_H

class MainMenuListener
{
    public:
        virtual void LoadInstancePressed(std::string& file_name) = 0;
        virtual void SaveInstancePressed(std::string& file_name) = 0;
        virtual void NewInstancePressed() = 0;
        virtual void NewStagePressed() = 0;
};
#endif