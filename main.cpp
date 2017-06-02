#include "test/ConditionTest.h"

int main(int argc, char **argv) {
    GoalBase::Instance()->add(Nutrition::Instance());

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}
