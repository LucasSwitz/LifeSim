#include <stddef.h>
#include <iostream>
#include <gtest/gtest.h>

#include "src/game/PMIDGRunner.h"
#include "src/game/mode/ProgramModeEditor.h"

#include "test/lua_tests/systems/ScriptableSystemTest.h"
#include "test/events/EventManagerTest.h"
#include "test/lua_tests/entity/ScriptableEntityTest.h"
#include "test/game/game_systems/CollisionSystemTest.h"
#include "test/game/game_components/ComponentUserBaseTest.h"
#include "test/world/InstanceTest.h"
#include "test/world/StageTest.h"
#include "test/protobuf/GameStateProtoBufTest.h"

int RunEditor();

int main(int argc, char **argv)
{
    Globals::SetResourceRoot("/home/lucas/Desktop/LifeSim/res");
    return RunEditor();
}

int RunEditor()
{
    PMIDGRunner runner;
    runner.Init(PMIDGRunner::EDITOR);
    runner.Run();
    return 0;
}