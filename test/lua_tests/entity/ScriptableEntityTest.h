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
    EXPECT_TRUE(entity->HasComponent("Physics"));
    EXPECT_TRUE(entity->HasComponent("Graphics"));
}

TEST_F(ScriptableEntityTest, ComponentValueTest)
{
    EXPECT_EQ(10,entity->GetComponentValueFloat("Physics","mass"));
    EXPECT_EQ(20,entity->GetComponentValueFloat("Physics","max_velocity"));

    EXPECT_EQ("test/file/path", entity->GetComponentValueString("Graphics","still_frame"));
}

TEST_F(ScriptableEntityTest, ManualIdSet)
{
    EXPECT_EQ(999, entity->ID());
}