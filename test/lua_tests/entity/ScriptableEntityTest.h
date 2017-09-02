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
    EXPECT_EQ(90,entity->GetComponentValueFloat("Position","x"));
    EXPECT_EQ(90,entity->GetComponentValueFloat("Position","y"));

    EXPECT_EQ("/home/lucas/Desktop/LifeSim/res/sprites/8_Bit_Mario.png", entity->GetComponentValueString("Graphics","sprite"));
}

TEST_F(ScriptableEntityTest, ManualIdSet)
{
    EXPECT_EQ(0, entity->ID());
}