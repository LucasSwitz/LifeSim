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


        StateScriptFactory::Instance()->PopulateFactory();

        ScriptableState* global_state = new ScriptableState();
        ScriptableState* transition_state1 = new ScriptableState();
        ScriptableState* transition_state2 = new ScriptableState();
    }
};


TEST_F(ScriptableStateMachineTest, TestGlobalState)
{
    scriptable_character->GetStateMachine()->SetGlobalState(
        StateScriptFactory::Instance()->GetScriptableState("Character", "GlobalTest"));

    scriptable_character->Tick();

    EXPECT_EQ(1, scriptable_character->GetInternalValue("ExecuteGlobalState"));
}

TEST_F(ScriptableStateMachineTest, TestStateTransition)
{
    scriptable_character->GetStateMachine()->SetCurrentState(
        StateScriptFactory::Instance()->GetScriptableState("Character", "TransitionState1"));


    scriptable_character->Tick();

    EXPECT_EQ(1, scriptable_character->GetInternalValue("ExecuteTransitionState1"));
    EXPECT_EQ(1, scriptable_character->GetInternalValue("ExitTransitionState1"));
    EXPECT_EQ(1, scriptable_character->GetInternalValue("EnterTransitionState2"));

    scriptable_character->Tick();

    EXPECT_EQ(1, scriptable_character->GetInternalValue("ExecuteTransitionState2"));

}