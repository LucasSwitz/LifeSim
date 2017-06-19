#include <stddef.h>
#include <iostream>
#include <gtest/gtest.h>
#include "test/lua_tests/actors/ActionScriptTest.h"
#include "test/lua_tests/actors/ScriptableStateMachineTest.h"
#include "test/lua_tests/actors/ScriptableStateMachineTest.h"
#include "test/lua_tests/entity/ScriptableEntityTest.h"
#include "test/lua_tests/systems/ScriptableSystemTest.h"
#include "test/lua_tests/systems/ScriptableSystemTest.h"
#include "test/game/GameRunnerTest.h"




int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

