#include "GoalScript.h"
#include "src/game_objects/actor/Actor.h"

GoalScript::GoalScript() : check_function(nullptr), priority_function(nullptr), is_fullfilled_function(nullptr),
    start_function(nullptr),end_function(nullptr)
{

}


void GoalScript::Start(Actor &actor)
{
    if (start_function)
    {
        try
        {
            (*start_function)(actor);
        }
        catch (luabridge::LuaException const &e)
        {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
    }
}

bool GoalScript::IsFullfilled(Actor &actor)
{
    bool is_fullfilled = false;
    if (is_fullfilled_function)
    {
        try
        {
            is_fullfilled = (*is_fullfilled_function)(actor);
        }
        catch (luabridge::LuaException const &e)
        {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
    }

    return is_fullfilled;
}

int GoalScript::Priority(Actor &actor)
{
    int priority = 0;
    if (priority_function)
    {
        try
        {
            priority = (*priority_function)(actor);
        }
        catch (luabridge::LuaException const &e)
        {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
    }
    return priority;
}

void GoalScript::End(Actor &actor)
{
    if (end_function)
    {
        try
        {
            (*end_function)(actor);
        }
        catch (luabridge::LuaException const &e)
        {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
    }
}

void GoalScript::Check(Actor &actor)
{
    if (check_function)
    {
        try
        {
            (*check_function)(actor);
        }
        catch (luabridge::LuaException const &e)
        {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
    }
}