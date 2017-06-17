#include "test/lua_tests/LuaTest.h"
#include "src/game_objects/LuaEntityFactory.h"


class ScriptableEntityTest : public LuaTest
{

    ScriptableEntityTest()
    {
        LuaEntityFactory::Instance()->PopulateFactory();
    }
    
    void SetUp()
    {
        scriptable_character = new Character();
    }

}