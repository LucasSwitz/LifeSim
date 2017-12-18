#include <stddef.h>
#include <iostream>
#include <gtest/gtest.h>
#include "src/utils/Globals.h"

#include "test/lua_tests/systems/ScriptableSystemTest.h"
#include "test/events/EventManagerTest.h"
#include "test/lua_tests/entity/ScriptableEntityTest.h"
#include "test/game/game_systems/CollisionSystemTest.h"
#include "test/game/game_components/ComponentUserBaseTest.h"
#include "test/world/InstanceTest.h"
#include "test/world/StageTest.h"
#include "test/protobuf/GameStateProtoBufTest.h"
#include "test/game/game_systems/GameSystemsLoadTest.h"

int RunTests(int argc, char** argv);

int main(int argc, char **argv)
{
    Globals::SetResourceRoot("/home/lucas/Desktop/ThunderBiscuit/test/res");
    return RunTests(argc,argv);
}


int RunTests(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}