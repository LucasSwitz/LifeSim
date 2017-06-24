#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include <list>
#include <unordered_map>
#include "src/system/ScriptableSystem.h"
#include "src/utils/ScriptFactory.h"

class SystemController : public ScriptFactory<ScriptableSystem>
{
public:
  ScriptableSystem *Configure(std::string full_script_path, std::string scriptable_name) override;

  void AddScript(Preamble &pre, ScriptableSystem *scriptable_object) override;

  void Init();

  bool Initialzed();

  void AddToSystemExecutionSequence(System *system);
  System *GetSystem(std::string name);

  const System *GetSystemInExecutionSequenceAt(int index);

  int GetSequenceSize();

  void Update(double seconds_since_last_update);

  void Reset() override
  {
    _initialized = false;
    _systems_execution_sequence.clear();
    _system_directory.clear();
  }
  bool SystemExists(std::string name);

  static SystemController *Instance()
  {
    static SystemController instance("/home/lucas/Desktop/LifeSim/lua_scripts/systems", "System");

    return &instance;
  }

protected:
  SystemController(std::string system_scripts_path, std::string script_type) : ScriptFactory<ScriptableSystem>(system_scripts_path, script_type, true){};

  std::list<System *> _systems_execution_sequence;
  std::unordered_map<std::string, System *> _system_directory;

private:
  bool _initialized = false;
};

#endif