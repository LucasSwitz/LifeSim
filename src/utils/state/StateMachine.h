#ifndef STATEMACHINE_H
#define STATEMACHINE_H


template<typename T>
class StateMachine
{

public:
    StateMachine(T* state_owner)
    {
        _state_owner = state_owner;
    }

    void Update()
    {
        if(_current_state) _current_state->Execute();

        if(_global_state) _global_state->Exceute();
    }

    void ChangeState(State<T>* _new_state)
    {
        if(_current_state)
        {
            _previous_state = _current_state;
            _current_state->End();
        }

        _current_state = _new_state;

        _new_state->Enter();
    }

    void SetCurrentState(State<T>* new_state)
    {
        _current_state = new_state;
    }

    void SetGlobalState(State<T>* new_gobal_state)
    {
        _global_state = new_global_state;
    }


private:
    T* _state_owner;
    State<T>* _current_state;
    State<T>* _previous_state;
    State<T>* _global_state;
};

#endif