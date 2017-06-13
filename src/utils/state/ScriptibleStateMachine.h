#include "src/utils/StateScriptFactory.h"

template<typename T>
class ScriptibleStateMachine : StateMachine
{

public:
    void SetCurrentState(std::string type_name, std::string script_name)
    {
        ScriptibleState<T>* new_current_state = StateScriptFactory::GetScriptibleState(type_name,script_name);
        StateMachine::SetCurrentState(new_current_state);
    }
}