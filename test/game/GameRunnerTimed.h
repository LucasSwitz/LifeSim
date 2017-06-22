#ifndef GAMERUNNERTIME_H
#define GAMERUNNERTIME_H

#include "src/game/GameRunner.h"
class GameRunnerTimed : public GameRunner
{
    public:
        void RunFor(double seconds)
        {
            std::cout << "Timed Game Runner Running For: " << seconds << " seconds." << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            double duration = 0;
            while(duration <= seconds) //will always skip last second. Should round to a certian magnitude.
            {
                this->Update();
                auto current_time = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - start).count();
            }

        }
};

#endif