#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/game_objects/LuaEntityFactory.h"

class ScriptableEntityTest : public LuaTest
{
  public:
    LuaEntity* scriptable_character;

    ScriptableEntityTest()
    {
        LuaEntityFactory::Instance()->PopulateFactory();
    }

    void SetUp()
    {
       scriptable_character = LuaEntityFactory::Instance()->GetEntity("TestEntity");
    }
};

TEST_F(ScriptableEntityTest, HasComponentTest)
{
    EXPECT_TRUE(scriptable_character->HasComponent("Physics"));
    EXPECT_TRUE(scriptable_character->HasComponent("Graphics"));
}

TEST_F(ScriptableEntityTest, ComponentValueTest)
{
    const Component* physics_component = scriptable_character->GetComponent("Physics");
    const Component* graphics_component = scriptable_character->GetComponent("Graphics");

    EXPECT_EQ(10,physics_component->GetFloatValue("mass"));
    EXPECT_EQ(20,physics_component->GetFloatValue("max_velocity"));

    EXPECT_EQ("test/file/path", graphics_component->GetStringValue("sprite_file"));
}

TEST_F(ScriptableEntityTest, ManualIdSet)
{
    EXPECT_EQ(999, scriptable_character->ID());
}