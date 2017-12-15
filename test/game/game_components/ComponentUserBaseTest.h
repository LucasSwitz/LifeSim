#ifndef COMPONENTUSERBASETEST_H
#define COMPONENTUSERBASETEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/component/ComponentUserBase.h"
#include "src/game_objects/LuaEntityFactory.h"
#include "src/utils/Globals.h"

class ComponentUserBaseTest : public LuaTest
{
    public:
        GameState g;
        ComponentUser* user_1;
        ComponentUser* user_2;
        
        ComponentUserBaseTest()
        {
            LuaEntityFactory::Instance()->PopulateFactory(Globals::RESOURCE_ROOT);
            user_1 = LuaEntityFactory::Instance()->GetEntityByName("TestComponentEntity1");
            user_2 = LuaEntityFactory::Instance()->GetEntityByName("TestComponentEntity2");
        }
};

/*TEST_F(ComponentUserBaseTest, SingleComponent)
{
    const std::list<ComponentUser*>* comps = g.GetComponentUserBase()->GetAllUsersWithComponent("TestComponent1");
    bool contains_user_1 = (std::find(comps->begin(), comps->end(), user_1) != comps->end());
    bool contains_user_2 = (std::find(comps->begin(), comps->end(), user_2) != comps->end());
    ASSERT_TRUE(contains_user_1);
    ASSERT_TRUE(contains_user_2);
}

TEST_F(ComponentUserBaseTest, MultipleComponents)
{
    const std::list<ComponentUser*>* comps = g.GetComponentUserBase()->GetAllUsersWithComponent({"TestComponent1", "TestComponent2"});
    bool contains_user_1 = (std::find(comps->begin(), comps->end(), user_1) != comps->end());
    bool contains_user_2 = (std::find(comps->begin(), comps->end(), user_2) != comps->end());
    ASSERT_TRUE(contains_user_1);
    ASSERT_FALSE(contains_user_2);
}*/


#endif
