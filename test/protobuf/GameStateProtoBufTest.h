#ifndef GAMESTATEPROTOBUFTEST_H
#define GAMESTATEPROTOBUFTEST_H

#include <gtest/gtest.h>
#include "src/protobuf/wrappers/GameStateProtoBufWrapper.h"

class GameStateProBufTest : public ::testing::Test
{
  public:
    Stage *s = nullptr;

    GameStateProBufTest()
    {
        LuaStageFactory::Instance()->PopulateFactory(Globals::RESOURCE_ROOT);
        SystemFactory::Instance()->PopulateFactory(Globals::RESOURCE_ROOT);
    }

    void SetUp()
    {
        s = LuaStageFactory::Instance()->GetStage("TestStage");
    }

    void TearDown()
    {
        delete s;
    }
};

TEST_F(GameStateProBufTest, TestAddEntities)
{
    GameStateProtoBufWrapper game_state_proto_buf;

    std::list<Entity *> entities =
        {
            new Entity(0, "TestEntity1", 0),
            new Entity(0, "TestEntity2", 1),
            new Entity(0, "TestEntity3", 2)};

    LuaStageFactory::Instance()->PopulateFactory(Globals::RESOURCE_ROOT);

    game_state_proto_buf.SetEntities(entities);
    game_state_proto_buf.SetStage(*s);
    game_state_proto_buf.ToFile("proto_buf_entity_output.pmidg");
}

TEST_F(GameStateProBufTest, TestGetEntities)
{
    GameStateProtoBufWrapper game_state_proto_buf;
    game_state_proto_buf.FromFile("proto_buf_entity_output.pmidg");

    std::vector<Entity *> entities;

    game_state_proto_buf.GetEntities(entities);

    ASSERT_EQ(3, entities.size());
    ASSERT_EQ(0, entities[0]->ID());
    ASSERT_EQ(1, entities[1]->ID());
    ASSERT_EQ(2, entities[2]->ID());
}

TEST_F(GameStateProBufTest, AddSystemTest)
{
    GameStateProtoBufWrapper game_state_proto_buf;

    std::list<System *> systems =
        {
            SystemFactory::Instance()->GetSystem("TestSystem1"),
            SystemFactory::Instance()->GetSystem("TestSystem2"),
            SystemFactory::Instance()->GetSystem("TestSystem3")};

    game_state_proto_buf.SetSystems(systems);
    game_state_proto_buf.SetStage(*s);
    game_state_proto_buf.ToFile("proto_buf_system_output.pmidg");
}

TEST_F(GameStateProBufTest, GetSystemsTest)
{
    GameStateProtoBufWrapper game_state_proto_buf;

    game_state_proto_buf.FromFile("proto_buf_system_output.pmidg");

    std::vector<std::string> systems;

    game_state_proto_buf.GetSystems(systems);

    ASSERT_EQ(3, systems.size());
    ASSERT_EQ("TestSystem1", systems[0]);
    ASSERT_EQ("TestSystem2", systems[1]);
    ASSERT_EQ("TestSystem3", systems[2]);
}
#endif