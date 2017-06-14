#include "test/lua_tests/LuaTest.h"
#include "src/game_objects/actor/character/Character.h"
#include "src/utils/state/StateScriptFactory.h"

class ScriptableStateMachineTest : public LuaTest
{
    public:
    Character* scriptable_character;
    void SetUp()
    {
        LuaTest::SetUp();
        scriptable_character = new Character();

        ScriptableState* global_state = new ScriptableState();
        global_state->LoadScript(L, "/home/lucas/Desktop/LifeSim/lua_scripts/state/character_state/CharacterGlobalState.lua","CharacterGlobalState");
        StateScriptFactory::Instance()->AddScriptableState("Character", "Global", global_state);

        scriptable_character->GetStateMachine()->SetGlobalState(
            StateScriptFactory::Instance()->GetScriptableState("Character", "Global"));
    }
};


TEST_F(ScriptableStateMachineTest, TestGlobalState)
{
    scriptable_character->Tick();
}