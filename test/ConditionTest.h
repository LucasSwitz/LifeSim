#include "src/game_objects/actor/goal/Nutrition.h"
#include <gtest/gtest.h>

class CondtionTest : public ::testing::Test
{

public:

   void SetUp()
    {
        GoalBase::Instance()->add(Nutrition::Instance());
        _test_actor = new Actor();
        _test_actor->AddGoal("Nutrition");
    }

    void TearDown()
    {
        delete _test_actor;
    }

  protected:
    Actor* _test_actor;
};

TEST_F(CondtionTest, TestStarved)
{
    _test_actor->UpdateInternalValue("Hunger",5);
    _test_actor->Tick();
    EXPECT_TRUE(_test_actor->HasCondition("Starved"));
}

TEST_F(CondtionTest, TestNotStarved)
{
    _test_actor->UpdateInternalValue("Hunger",20);
    _test_actor->Tick();
    EXPECT_FALSE(_test_actor->HasCondition("Starved"));
}