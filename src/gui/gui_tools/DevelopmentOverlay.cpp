#include "DevelopmentOverlay.h"

DevelopmentOverlay::DevelopmentOverlay()
{

}

void DevelopmentOverlay::Init(sf::RenderWindow& window)
{
    ImGui::SFML::Init(window);
    _log.Clear();
}

Log& DevelopmentOverlay::GetLog()
{
    return _log;
}

void DevelopmentOverlay::Draw(sf::RenderWindow& window, sf::Time& deltaTime)
{
    /*sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);*/
    sf::Event event;
    ImGui::SFML::Update(window, deltaTime);

// #### DESIGN GUI HERE
    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");

    _log.Draw("Log");
    _entity_table.Draw("Entities");
    ImGui::End();

// #### RENDER GUI HERE
    ImGui::SFML::Render(window);
}

void DevelopmentOverlay::Shutdown()
{
    ImGui::SFML::Shutdown();
}
