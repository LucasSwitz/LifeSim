#include "ActionScript.h"
#include "src/game_objects/actor/Actor.h"

ActionScript::ActionScript(Actor* performer) : _performer(performer),
    start_function(nullptr), perform_function(nullptr), is_finished_function(nullptr) {}

void ActionScript::Start()
{
    if (start_function)
    {
        try
        {
            (*start_function)();
            std::cout << "I think it started?" << std::endl;
        }
        catch (luabridge::LuaException const &e)
        {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
    }
    else
    {
        std::cout << "NO START FUNCTIOn" << std::endl;

    }
}

void ActionScript::Perform()
{
    if (perform_function)
    {
        try
        {
            (*perform_function)();
        }
        catch (luabridge::LuaException const &e)
        {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
    }
}

bool ActionScript::IsFinished()
{
    if (is_finished_function)
    {
        try
        {
            (*is_finished_function)();
        }
        catch (luabridge::LuaException const &e)
        {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
    }
    else
    {
        return true;
    }
}

std::string ActionScript::GetName()
{
    return _action_name;
}

void ActionScript::LoadScript(luabridge::lua_State *L, const std::string &script_path, const std::string &action_name)
    {
        using namespace luabridge;
        _action_name = action_name;
        if (luaL_dofile(L, script_path.c_str()) == 0)
        {
            LuaRef action_table = getGlobal(L, action_name.c_str());
            std::cout << "Did File!" << std::endl;
            if (action_table.isTable())
            {
                std::cout << "Is Table!" << std::endl;

                if (action_table["SetPerformer"].isFunction())
                {
                    luabridge::LuaRef set_performer_function = action_table["SetPerformer"];
                    (set_performer_function)(_performer->ID());
                }
                else
                {
                    return; //throw exception
                }

                if (action_table["Start"].isFunction())
                {
                    std::cout << "Start Function!" << std::endl;

                    start_function = std::make_unique<LuaRef>(action_table["Start"]);
                }

                if (action_table["Perform"].isFunction())
                {
                    std::cout << "Perform Function!" << std::endl;

                    perform_function = std::make_unique<LuaRef>(action_table["Perform"]);
                }

                if (action_table["IsFinished"].isFunction())
                {
                    std::cout << "Finished Function!" << std::endl;

                    is_finished_function = std::make_unique<LuaRef>(action_table["IsFinshed"]);
                }
            }
        }
        else
        {
            std::cout << "Error, can't open script: " << script_path << std::endl;
        }
    }