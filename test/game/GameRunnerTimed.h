#ifndef GAMERUNNERTIME_H
#define GAMERUNNERTIME_H

#include "src/game/GameRunner.h"
#include "src/utils/logging/Logging.h"
#include "src/event/EventSubscriber.h"
#include "src/event/EngineEventManager.h"

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

        void RunTillClose()
        {
            EngineEventManager::Instance()->RegisterSubscriber(this);

            if(!Initialized())
            {
                std::cout << "GameRunner Not Initialized!" << std::endl;
                return;
            }

            while(!_window_closed)
            {
                this->Update();
            }
        }

        void OnEvent(Event& e) override
        {
            if(e.id == EventType::CLOSE_WINDOW_EVENT)
            {
                _window_closed = true;
            }

            GameRunner::OnEvent(e);
        }

        std::list<Subscription> GetSubscriptions()
        {
            std::list<Subscription> list = {Subscription(EventType::CLOSE_WINDOW_EVENT)};
            return list;
        }

    private:
    bool _window_closed = false;
};

#endif