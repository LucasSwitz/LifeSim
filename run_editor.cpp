#include <stddef.h>
#include <iostream>

#include "src/game/PMIDGRunner.h"
#include "src/game/mode/ProgramModeEditor.h"

int RunEditor();

int main(int argc, char **argv)
{
    Globals::SetResourceRoot("/home/lucas/Desktop/ThunderBiscuit/res");
    return RunEditor();
}

int RunEditor()
{
    PMIDGRunner runner;
    runner.Init(PMIDGRunner::EDITOR);
    runner.Run();
    return 0;
}