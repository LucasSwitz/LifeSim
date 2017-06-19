#include "ConditionScript.h"

void Condition::Start(Actor &t)
{
    if (_start_function)
    {
        try
        {
            (*_start_function)(t);
        }
        catch (luabridge::LuaException const &e)
        {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
    }
};

void Condition::Update(Actor &t)
{
    if (_update_function)
    {
        try
        {
                (*_update_function)(t);
        }
        catch (luabridge::LuaException const &e)
        {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
    }
}

void Condition::End(Actor &t)
{
    if (_end_function)
    {
        try
        {
            (*_end_function)(t);
        }
        catch (luabridge::LuaException const &e)
        {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
    }
};

bool Condition::isFinished(Actor &t)
{
    if (_is_finished_function)
    {
        try
        {
            (*_is_finished_function)(t);
        }
        catch (luabridge::LuaException const &e)
        {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
    }
};

Condition *Condition::Instance()
{
    static Condition instance;
    return &instance;
}

void Condition::LoadScript(luabridge::lua_State *L, const std::string &script_path, const std::string &condition_name)
{
    using namespace luabridge;
    if (luaL_dofile(L, script_path.c_str()) == 0)
    {
        LuaRef condition_table = getGlobal(L, condition_name.c_str());
        if (condition_table.isTable())
        {
            if (condition_table["Start"].isFunction())
            {
                _start_function = std::make_unique<LuaRef>(condition_table["Start"]);
            }

            if (condition_table["Update"].isFunction())
            {
                _update_function = std::make_unique<LuaRef>(condition_table["Update"]);
            }

            if (condition_table["End"].isFunction())
            {
                _end_function = std::make_unique<LuaRef>(condition_table["End"]);
            }
            if (condition_table["IsFinished"].isFunction())
            {
                _is_finished_function = std::make_unique<LuaRef>(condition_table["IsFinished"]);
            }
        }
    }
    else
    {
        std::cout << "Error, can't open script!" << std::endl;
    }
};