#ifndef SCIPTABLESTATEMACHINETEST_H
#define SCIPTABLESTATEMACHINETEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/game_objects/actor/character/Character.h"
#include "src/utils/state/StateScriptFactory.h"

class ScriptableStateMachineTest : public LuaTest
{
    public:
    Character* scriptable_entity;

    ScriptableStateMachineTest()
    {
        StateScriptFactory::Instance()->PopulateFactory();
    }
    
    void SetUp()
    {
        scriptable_character = LuaEntityFactory::Instance()->GetEntity("TestEntity");
    }
};

TEST_F(ScriptableStateMachineTest, TestGlobalState)
{
    scriptable_entity->GetStateMachine()->SetGlobalState(
        StateScriptFactory::Instance()->GetScriptableState("Character", "GlobalStateTest"));

    scriptable_entity->Tick();

    EXPECT_EQ("ExecuteTestGlobalState", scriptable_entity.GetComponentValueString("Debug","flag"));
}

TEST_F(ScriptableStateMachineTest, TestStateTransition)
{
    scriptable_entity->GetStateMachine()->SetCurrentState(
        StateScriptFactory::Instance()->GetScriptableState("Character", "TransitionState1"));

    scriptable_entity->Tick();

    EXPECT_EQ("ExecuteTransitionState1", scriptable_entity.GetComponentValueString("Debug","flag"));

    EXPECT_EQ("ExitTransitionState1", scriptable_entity.GetComponentValueString("Debug","flag"));

    EXPECT_EQ("EnterTransitionState2", scriptable_entity.GetComponentValueString("Debug","flag"));

    scriptable_entity->Tick();

    EXPECT_EQ("ExecuteTransitionState2", scriptable_entity.GetComponentValueString("Debug","flag"));

}

#endif