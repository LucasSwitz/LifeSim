#ifndef COMPONENTUSERBASETEST_H
#define COMPONENTUSERBASETEST_H

#include "test/lua_tests/lua_core/LuaTest.h"
#include "src/component/ComponentUserBase.h"
#include "src/game_objects/LuaEntityFactory.h"

class ComponentUserBaseTest : public LuaTest
{
    public:
        ComponentUser* user_1;
        ComponentUser* user_2;
        
        ComponentUserBaseTest()
        {
            ComponentUserBase::Instance()->Reset();

            LuaEntityFactory::Instance()->PopulateFactory();
            user_1 = LuaEntityFactory::Instance()->GetEntity("TestComponentEntity1");
            user_2 = LuaEntityFactory::Instance()->GetEntity("TestComponentEntity2");
        }
};

TEST_F(ComponentUserBaseTest, SingleComponent)
{
    std::list<ComponentUser*> comps = ComponentUserBase::Instance()->GetAllUsersWithComponent("TestComponent1");
    bool contains_user_1 = (std::find(comps.begin(), comps.end(), user_1) != comps.end());
    bool contains_user_2 = (std::find(comps.begin(), comps.end(), user_2) != comps.end());
    ASSERT_TRUE(contains_user_1);
    ASSERT_TRUE(contains_user_2);
}

TEST_F(ComponentUserBaseTest, MultipleComponents)
{
    std::list<ComponentUser*> comps = ComponentUserBase::Instance()->GetAllUsersWithComponents({"TestComponent1", "TestComponent2"});
    bool contains_user_1 = (std::find(comps.begin(), comps.end(), user_1) != comps.end());
    bool contains_user_2 = (std::find(comps.begin(), comps.end(), user_2) != comps.end());
    ASSERT_TRUE(contains_user_1);
    ASSERT_FALSE(contains_user_2);
}


#endif
