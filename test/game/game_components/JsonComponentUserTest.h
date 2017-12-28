#ifndef JSONCOMPONENTUSERTEST_H
#define JSONCOMPONENTUSERTEST_H

#include "src/component/ComponentUser.h"
#include "src/component/ComponentUserType.h"
#include "src/utils/json/json.hpp"
#include <gtest/gtest.h>
#include <fstream>

using json = nlohmann::json;

class JsonComponentUserTest : public ::testing::Test
{
  public:
    JsonComponentUserTest()
    {
    }

    void SetUp()
    {
    }
};

TEST_F(JsonComponentUserTest, TestUIHasComponents)
{
    std::ifstream input(Res("TestJsonComponentUser.json"));

    json cu_json;
    input >> cu_json;

    ptr<ComponentUser> user = ComponentUser::FromJson(CU_TYPE_ENTITY, cu_json);

    ASSERT_TRUE(user->HasComponent("Position"));
    ASSERT_EQ(user->GetComponentValueFloat("Position", "x"), 5);
    ASSERT_EQ(user->GetComponentValueFloat("Position", "y"), 5);
};

#endif
