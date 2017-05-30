#include <cppunit/TestFixture.h>
#include "src/game_objects/actor/needs/Nutrition.h"
#include "src/game_objects/actor/Actor.h"

class TestActor : public Actor
{
  public:
    TestActor(){};
    SetHungerWrap(int hunger) { SetHunger(hunger); }
};

class NutritionTest : public CppUnit::TestFixture
{
  public:
    static CppUnit::Test *suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("NutritionTest");
        suiteOfTests->addTest(new CppUnit::TestCaller<NutritionTest>(
            "testStarved",
            &NutritionTest::testStarved));
        return suiteOfTests;
    }

    void setUp()
    {
        
    }

    void tearDown()
    {
        
    }

    void testStarved()
    {
        _actor.SetHungerWrap(5);
        Nutrition::Instance()->Check(_actor);
        CPPUNIT_ASSERT(_actor.HasCondition("Starved"));
    }

  private:
    TestActor _actor;
};