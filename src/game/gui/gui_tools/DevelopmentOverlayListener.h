#ifndef DEVELOPMENTOVERLAYLISTENER_H
#define DEVELOPMENTOVERLAYLISTENER_H

class DevelopmentOverlayListener
{
    public:
        virtual void OnCreateBlankInstance(int width, int height) = 0;
};

#endif