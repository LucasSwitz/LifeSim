#ifndef GAMERUNNERTIME_H
#define GAMERUNNERTIME_H

#include "src/game/GameRunner.h"
#include "src/utils/logging/Logging.h"

class GameRunnerTimed : public GameRunner
{
    public:
        void RunFor(double seconds)
        {
            LOG->LogInfo(1,"Starting GameRunner for: %f seconds. \n", seconds);
            auto start = std::chrono::high_resolution_clock::now();
            double duration = 0;
            while(duration <= seconds) //will always skip last second. Should round to a certian magnitude.
            {
                this->Update();
                auto current_time = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - start).count();
            }

            this->Shutdown();
        }
};

#endif