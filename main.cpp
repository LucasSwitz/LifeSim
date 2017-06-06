#include "test/ConditionTest.h"
#include "test/ActionsTest.h"
#include "src/utils/Statics.h"

int main(int argc, char **argv) {
  Statics::Init();
  
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
