#include "src/game_objects/actor/actions/ActionEat.h"
#include "src/game_objects/actor/actions/ActionFactory.h"
#include "src/game_objects/actor/goal/Nutrition.h"
#include "src/game_objects/items/Apple.h"
#include "src/game_objects/EntityManager.h"
#include <gtest/gtest.h>

class ActionsTest : public ::testing::Test
{
  public:
    void SetUp()
    {
        Apple* apple = new Apple();
        _test_actor = new Actor();

        //add action to nutrition command chain
        Nutrition::Instance()->AddActionScript("EAT -id " + std::to_string(apple->ID()));

        //create actor and add Nutrition as its Goal
        _test_actor->AddGoal("Nutrition");
    }

    void TearDown()
    {
        delete _test_actor;
    }

  protected:
    Actor *_test_actor;
};

TEST_F(ActionsTest, TestDescriptors)
{
    ActionDescriptor d("EAT -id 5");
    EXPECT_EQ(d.action, "EAT");
    EXPECT_EQ(d.flags.at("id"), "5");
}

TEST_F(ActionsTest, TestAddEatAction)
{
    //set hungry enough to eat
    _test_actor->UpdateInternalValue("Hunger", 5);

    //check if eating has been set as current action
    _test_actor->Tick();
    Action *_current_action = _test_actor->GetCurrentAction();
    EXPECT_EQ(_current_action->GetName(), "EAT");
}