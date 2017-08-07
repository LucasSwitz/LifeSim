#ifndef FPSRUNNABLE_H
#define FPSRUNNABLE_H

/**
    Purpose: Classes can implement the FPSRunnable interface to be controlled by an FPSRunner.
             The Load() method is called once before the FPSRunnable starts ticking and the
             Unload() method is called once after the FPSRunner has stopped operating. 
**/

class FPSRunnable
{
    public:
    
    virtual void Load() = 0;
    virtual void Tick(float seconds_elapsed) = 0;
    virtual void Unload() = 0;
};

#endif