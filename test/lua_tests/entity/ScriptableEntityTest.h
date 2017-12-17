#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/game_objects/LuaEntityFactory.h"

class ScriptableEntityTest : public LuaTest
{
  public:
    Entity* entity;
    ScriptableEntityTest()
    {
        LuaEntityFactory::Instance()->PopulateFactory(Globals::RESOURCE_ROOT);
        entity = LuaEntityFactory::Instance()->GetEntityByName("ScriptableTestEntity");
    }
};

TEST_F(ScriptableEntityTest, HasComponentTest)
{
    EXPECT_TRUE(entity->HasComponent("Position"));
    EXPECT_TRUE(entity->HasComponent("Graphics"));
}

TEST_F(ScriptableEntityTest, ComponentValueTest)
{
    EXPECT_EQ(90,entity->GetComponentValueFloat("Position","x"));
    EXPECT_EQ(90,entity->GetComponentValueFloat("Position","y"));

    EXPECT_EQ(Res("mario_1.png"), entity->GetComponentValueString("Graphics","sprite"));
}

TEST_F(ScriptableEntityTest, ID)
{
    EXPECT_EQ(1, entity->ID());
}