#include <stddef.h>
#include <iostream>
#include <gtest/gtest.h>
#include "test/lua_tests/ActionScriptTest.h"
#include "test/lua_tests/actors/ScriptableStateMachineTest.h"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

