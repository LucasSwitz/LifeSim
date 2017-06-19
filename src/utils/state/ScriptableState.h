#ifndef SCRIPTIBLE_STATE
#define SCRIPTIBLE_STATE

#include "src/utils/lua/LuaUniversal.h"
#include <memory>

class ScriptableState
{
public:
  template <typename T>
  void Enter(T *t)
  {
    if (_enter_function)
    {
      (*_enter_function)(t);
    }
  };

  template <typename T>
  void Execute(T *t)
  {
    if (_execute_function)
    {
      (*_execute_function)(t);
    }
  };

  template <typename T>
  void Exit(T *t)
  {
    if (_exit_function)
    {
      (*_exit_function)(t);
    }
  };

  void LoadLuaRef(LuaRef &ref)
  {
  }

  void LoadScript(luabridge::lua_State *L, const std::string &script_path, const std::string &state_name)
  {
    using namespace luabridge;
    _state_name = state_name;

    if (luaL_dofile(L, script_path.c_str()) == 0)
    {
      LuaRef action_table = getGlobal(L, state_name.c_str());
      if (action_table.isTable())
      {
        if (action_table["Enter"].isFunction())
        {
          _enter_function = std::make_unique<LuaRef>(action_table["Enter"]);
        }

        if (action_table["Execute"].isFunction())
        {
          _execute_function = std::make_unique<LuaRef>(action_table["Execute"]);
        }

        if (action_table["Exit"].isFunction())
        {
          _exit_function = std::make_unique<LuaRef>(action_table["Exit"]);
        }
      }
    }
    else
    {
      std::cout << "Error, can't open script: " << script_path << std::endl;
    }
  }

private:
  std::unique_ptr<luabridge::LuaRef> _enter_function;
  std::unique_ptr<luabridge::LuaRef> _execute_function;
  std::unique_ptr<luabridge::LuaRef> _exit_function;
  std::string _state_name;
};

#endif