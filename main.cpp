#include <stddef.h>
#include <iostream>
#include <gtest/gtest.h>
//#include "test/lua_tests/actors/ActionScriptTest.h"
//#include "test/lua_tests/actors/ScriptableStateMachineTest.h"
//#include "test/lua_tests/actors/ScriptableStateMachineTest.h"
//#include "test/lua_tests/systems/ScriptableSystemTest.h"
//#include "test/lua_tests/systems/ScriptableSystemTest.h"

#include "test/game/game_systems/RegenerationSystemTest.h"
#include "test/events/EventManagerTest.h"
#include "test/lua_tests/entity/ScriptableEntityTest.h"
#include "test/game/game_systems/CollisionSystemTest.h"
#include "test/game/game_components/ComponentUserBaseTest.h"
//#include "test/game/GameRunnerTest.h"
//#include "test/game/game_systems/GraphicsSystemTest.h"
//#include "test/game/game_systems/MoveableGraphicsSystemTest.h"
//#include "test/game/game_systems/KeyboardInputSystemTest.h"
#include "test/world/InstanceTest.h"
#include "test/world/StageTest.h"
// /#include "test/world/TileMapTest.h"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/*#include "imgui.h"
#include "imgui-SFML.h"
#include <stdarg.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    ExampleAppLog log;

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        log.AddLog("Hello World! %d \n",1);
        log.Draw("Log");


        window.clear();
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}*/