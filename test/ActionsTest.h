#include "src/game_objects/actor/actions/ActionEat.h"
#include "src/game_objects/actor/actions/ActionFactory.h"
#include "src/game_objects/actor/goal/Nutrition.h"
#include "src/game_objects/items/Apple.h"
#include "src/game_objects/EntityManager.h"
#include <gtest/gtest.h>

class TestNutrition : public Nutrition
{
  public:
    static TestNutrition *Instance()
    {
        static TestNutrition instance;
        return &instance;
    }

    void AddActionScriptWrap(std::string script) { AddActionScript(script); }
};

class ActionsTest : public ::testing::Test
{
  public:
    void SetUp()
    {
        Apple* apple = new Apple();
        _test_actor = new Actor();

        EntityManager::Instance()->RegisterEntity(*_test_actor);
        EntityManager::Instance()->RegisterEntity(*apple);

        //add action to nutrition command chain
        TestNutrition::Instance()->AddActionScriptWrap("Eat -id " + std::to_string(apple->ID()));

        //add nutrtion test to GoalBase
        GoalBase::Instance()->erase();
        GoalBase::Instance()->add(TestNutrition::Instance());

        ActionFactory::Instance()->AddAction(new ActionEat());

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
    ActionDescriptor d("Eat -id 5");
    EXPECT_EQ(d.action, "Eat");
    EXPECT_EQ(d.flags.at("id"), "5");
}

TEST_F(ActionsTest, TestAddEatAction)
{
    //set hungry enough to eat
    _test_actor->UpdateInternalValue("Hunger", 5);

    //check if eating has been set as current action
    _test_actor->Tick();
    Action *_current_action = _test_actor->GetCurrentAction();
    EXPECT_EQ(_current_action->_name, "Eat");
}