#ifndef GAMESTATEPROTOBUFTEST_H
#define GAMESTATEPROTOBUFTEST_H

#include <gtest/gtest.h>
#include "src/protobuf/wrappers/GameStateProtoBufWrapper.h"

class GameStateProBufTest : public ::testing::Test
{
    public:

    
    void SetUp()
    {

    }
};


TEST_F(GameStateProBufTest, TestAddEntities)
{
    GameStateProtoBufWrapper game_state_proto_buf;

    std::list<Entity*> entities = 
    {
        new Entity(0,"TestEntity1", 0),
        new Entity(0,"TestEntity2", 1),
        new Entity(0,"TestEntity3", 2)
    };

    Instance i;
    game_state_proto_buf.SetEntities(entities);
    //game_state_proto_buf.SetInstance(i);
    game_state_proto_buf.ToFile("proto_buf_entity_output.pmidg");
}

TEST_F(GameStateProBufTest, TestGetEntities)
{
    GameStateProtoBufWrapper game_state_proto_buf;
    game_state_proto_buf.FromFile("proto_buf_entity_output.pmidg");

    std::vector<Entity*> entities;

    game_state_proto_buf.GetEntities(entities); 

    ASSERT_EQ(3,entities.size());
    ASSERT_EQ(0,entities[0]->ID());
    ASSERT_EQ(1,entities[1]->ID());
    ASSERT_EQ(2,entities[2]->ID()); 
}

/*TEST_F(GameStateProBufTest, SaveToFileTest)
{
    GameStateProtoBufWrapper game_state_proto_buf;

    std::list<System*> systems  = 
    {
        new System("TestSystem1"),
        new System("TestSystem2"),
        new System("TestSystem3")
    };

    Instance i;
    game_state_proto_buf.SetSystems(systems);
    game_state_proto_buf.SetInstance(i);
    game_state_proto_buf.ToFile("proto_buf_system_output.pmidg");
}*/

TEST_F(GameStateProBufTest, ReadFromFile)
{
    GameStateProtoBufWrapper game_state_proto_buf;

    game_state_proto_buf.FromFile("proto_buf_system_output.pmidg");

    std::vector<std::string> systems;

    game_state_proto_buf.GetSystems(systems);

    ASSERT_EQ(3,systems.size());
    ASSERT_EQ("TestSystem1",systems[0]);
    ASSERT_EQ("TestSystem2",systems[1]);
    ASSERT_EQ("TestSystem3",systems[2]);    
}
#endif