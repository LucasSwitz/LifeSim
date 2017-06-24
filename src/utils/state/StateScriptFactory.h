#ifndef STATESCRIPTFACTORY_H
#define STATESCRIPTFACTORY_H

#include <unordered_map>
#include <iostream>
#include "src/utils/state/ScriptableState.h"
#include "src/utils/ScriptFactory.h"
#include "src/utils/lua/LuaUniversal.h"

class StateScriptFactory : public ScriptFactory<ScriptableState>
{

public:
  ScriptableState *GetScriptableState(std::string script_template_class, std::string script_name);

  ScriptableState *Configure(std::string full_script_path, std::string scriptable_name);

  void AddScript(Preamble &pre, ScriptableState *scriptable_object);

  static StateScriptFactory *Instance()
  {
    static StateScriptFactory instance("/home/lucas/Desktop/LifeSim/lua_scripts/states", "State");
    return &instance;
  };

private:
  StateScriptFactory(std::string script_path, std::string state_name) : ScriptFactory<ScriptableState>(script_path, state_name, true){};

  std::unordered_map<std::string, std::unordered_map<std::string, ScriptableState *>> _scripts_map;
};

#endif