#ifndef COMPONENTUSERBASETEST_H
#define COMPONENTUSERBASETEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/component/ComponentUserBase.h"
#include "src/game_objects/LuaEntityFactory.h"
#include "src/utils/Globals.h"

class ComponentUserBaseTest : public LuaTest
{
  public:
    ComponentUserBase cub;
    ptr<Entity> user_1;
    ptr<Entity> user_2;

    ComponentUserBaseTest()
    {
        }

    void SetUp()
    {
        LuaEntityFactory::Instance()->PopulateFactory(Globals::RESOURCE_ROOT);

        user_1 = ptr<Entity>(LuaEntityFactory::Instance()->GetEntityByName("TestComponentEntity1"));
        user_2 = ptr<Entity>(LuaEntityFactory::Instance()->GetEntityByName("TestComponentEntity2"));

        cub.AddComponentUser(user_1);
        cub.AddComponentUser(user_2);

        user_1->EnableAll();
        user_2->EnableAll();
        
    }
};

TEST_F(ComponentUserBaseTest, SingleComponent)
{
    auto comps =cub.GetAllUsersWithComponent("TestComponent1");
    bool contains_user_1 = (std::find(comps->begin(), comps->end(), user_1) != comps->end());
    bool contains_user_2 = (std::find(comps->begin(), comps->end(), user_2) != comps->end());
    ASSERT_TRUE(contains_user_1);
    ASSERT_TRUE(contains_user_2);
}

TEST_F(ComponentUserBaseTest, MultipleComponents)
{
    std::list<ptr<ComponentUser>> comps; 
    cub.GetAllUsersWithComponents({"TestComponent1", "TestComponent2"},comps);
    bool contains_user_1 = (std::find(comps.begin(), comps.end(), user_1) != comps.end());
    bool contains_user_2 = (std::find(comps.begin(), comps.end(), user_2) != comps.end());
    ASSERT_TRUE(contains_user_1);
    ASSERT_FALSE(contains_user_2);
}

#endif
