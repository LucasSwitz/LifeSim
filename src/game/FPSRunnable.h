#ifndef FPSRUNNABLE_H
#define FPSRUNNABLE_H

class FPSRunnable
{
    public:
    
    virtual void Load() = 0;
    virtual void Update(float seconds_elapsed) = 0;
    virtual void Unload() = 0;
};

#endif