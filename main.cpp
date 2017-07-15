#include <stddef.h>
#include <iostream>
#include <gtest/gtest.h>

//#include "test/lua_tests/actors/ActionScriptTest.h"
//#include "test/lua_tests/actors/ScriptableStateMachineTest.h"
//#include "test/lua_tests/actors/ScriptableStateMachineTest.h"
//#include "test/lua_tests/systems/ScriptableSystemTest.h"
//#include "test/lua_tests/systems/ScriptableSystemTest.h"

/*#include "test/game/game_systems/RegenerationSystemTest.h"
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
#include "test/world/TileMapTest.h"*/


#include "src/game/PMIDGRunner.h"
#include "src/game/mode/ProgramModeEditor.h"

int RunGUI();
int RunTests(int argc, char** argv);

int main(int argc, char **argv)
{
  if(argc > 1)
  {
    if(*argv[1] == 't')
    {
        return RunTests(argc,argv);
    }
    else if(*argv[1] == 'g')
    {
        return RunGUI();
    }
    else
    {

    }
  }
  else
  {
      return RunGUI();
  }
}

int RunGUI()
{
    PMIDGRunner runner;
    runner.Init(PMIDGRunner::EDITOR);
    runner.Run();
    return 0;
}

int RunTests(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}