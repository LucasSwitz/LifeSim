#ifndef STATEResourceFactory_H
#define STATEResourceFactory_H

#include <unordered_map>
#include <iostream>
#include "src/utils/state/ScriptableState.h"
#include "src/utils/ResourceFactory.h"
#include "src/utils/lua/LuaUniversal.h"

class StateResourceFactory : public ResourceFactory<ScriptableState>
{

public:
  ScriptableState *GetScriptableState(std::string script_template_class, std::string script_name);

  ScriptableState *Configure(std::string full_script_path, std::string scriptable_name);

  void AddResource(Preamble &pre, ScriptableState *scriptable_object);

  static StateResourceFactory *Instance()
  {
    static StateResourceFactory instance("State");
    return &instance;
  };

private:
  StateResourceFactory(std::string state_name) : ResourceFactory<ScriptableState>(state_name, true){};

  std::unordered_map<std::string, std::unordered_map<std::string, ScriptableState *>> _scripts_map;
};

#endif