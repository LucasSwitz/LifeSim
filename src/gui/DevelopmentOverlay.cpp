#include "DevelopmentOverlay.h"

DevelopmentOverlay::DevelopmentOverlay()
{
}

void DevelopmentOverlay::Init(sf::RenderWindow &render_window)
{
    ImGui::SFML::Init(window);
}

void DevelopmentOverlay::Draw(Time &deltaTime)
{
    /*sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);*/
    ExampleAppLog log;

    sf::Event event;

    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }

    ImGui::SFML::Update(window, deltaClock.restart());

// #### DESIGN GUI HERE
    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::End();

    log.AddLog("Hello World! %d \n", 1);
    log.Draw("Log");

// #### DESIGN GUI RENDER GUI HERE
    ImGui::SFML::Render(window);
}

ImGui::SFML::Shutdown()
{
    ImGui::SFML::Shutdown();
}
