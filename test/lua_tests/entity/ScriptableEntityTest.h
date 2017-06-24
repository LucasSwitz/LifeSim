#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/game_objects/LuaEntityFactory.h"

class ScriptableEntityTest : public LuaTest
{
  public:
    LuaEntity* entity;

    ScriptableEntityTest()
    {
        LuaEntityFactory::Instance()->PopulateFactory();
        entity = LuaEntityFactory::Instance()->GetEntity("TestEntity");
    }
};

TEST_F(ScriptableEntityTest, HasComponentTest)
{
    EXPECT_TRUE(entity->HasComponent("Position"));
    EXPECT_TRUE(entity->HasComponent("Graphics"));
}

TEST_F(ScriptableEntityTest, ComponentValueTest)
{
    EXPECT_EQ(0,entity->GetComponentValueFloat("Position","x_pos"));
    EXPECT_EQ(0,entity->GetComponentValueFloat("Position","y_pos"));

    EXPECT_EQ("still/sprite", entity->GetComponentValueString("Graphics","sprite"));
}

TEST_F(ScriptableEntityTest, ManualIdSet)
{
    EXPECT_EQ(999, entity->ID());
}