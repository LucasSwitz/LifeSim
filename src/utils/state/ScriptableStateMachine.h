#ifndef SCRIPTABLESTATEMACHINE_H
#define SCRIPTABLESTATEMACHINE_H

#include "src/utils/state/StateScriptFactory.h"
#include "src/utils/state/ScriptableState.h"

template<typename T>
class ScriptableStateMachine{

public:
    ScriptableStateMachine(T* owner) : _state_owner(owner){};

    void SetCurrentState(std::string type_name, std::string script_name)
    {
        _current_state = StateScriptFactory::Instance()->GetScriptableState(type_name,script_name);
    }

    void Update()
    {
        if(_current_state) _current_state->Execute<T>(_state_owner);

        if(_global_state)
        {
             _global_state->Execute<T>(_state_owner);
        }
    }


    void ChangeState(std::string type_name, std::string script_name)
    {
        ScriptableState* new_state = StateScriptFactory::Instance()->GetScriptableState(type_name,script_name);
         
        if(_current_state)
        {
            _previous_state = _current_state;

            _current_state->Exit<T>(_state_owner);
        }

        _current_state = new_state;

        _current_state->Enter<T>(_state_owner);
    }

    void SetCurrentState(ScriptableState* new_state)
    {
        _current_state = new_state;
    }

    void SetGlobalState(ScriptableState* new_global_state)
    {
        _global_state = new_global_state;
    }

private:
    T* _state_owner = nullptr;
    ScriptableState* _current_state = nullptr;
    ScriptableState* _previous_state = nullptr;
    ScriptableState* _global_state = nullptr;
};

#endif