#include "src/game_objects/actor/goal/Nutrition.h"
#include "src/game_objects/actor/Actor.h"
#include <gtest/gtest.h>

class TestActor : public Actor
{
  public:
    TestActor(){};
    void SetHungerWrap(int hunger) { SetHunger(hunger); }
};

class CondtionTest : public ::testing::Test
{

public:

   void SetUp()
    {
        GoalBase::Instance()->add(Nutrition::Instance());
        _test_actor = new TestActor();
        _test_actor->AddGoal("Nutrition");
    }

    void TearDown()
    {
        delete _test_actor;
    }

  protected:
    TestActor* _test_actor;
};

TEST_F(CondtionTest, TestStarved)
{
    _test_actor->SetHungerWrap(5);
    _test_actor->Tick();
    EXPECT_TRUE(_test_actor->HasCondition("Starved"));
}

TEST_F(CondtionTest, TestNotStarved)
{
    _test_actor->SetHungerWrap(20);
    _test_actor->Tick();
    EXPECT_FALSE(_test_actor->HasCondition("Starved"));
}