#include <stddef.h>
#include <iostream>

#include "src/game/TBRunner.h"
#include "src/game/mode/ProgramModeEditor.h"

int RunEditor();

int main(int argc, char **argv)
{
    Globals::SetResourceRoot("/home/lucas/Desktop/ThunderBiscuit/res");
    return RunEditor();
}

int RunEditor()
{
    TBRunner runner;
    runner.Init(TBRunner::EDITOR);
    runner.Run();
    return 0;
}