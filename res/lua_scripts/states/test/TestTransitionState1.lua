--PREAMBLE_START
ScriptType = "State"
StateOwner = "Character"
Name = "TransitionState1"
--PREAMBLE_END

TransitionState1 = {
    Enter=function(character)
        --character:SetInternalValue("EnterTransitionState1",1)
    end,
    Execute=function(character)
        --character:SetInternalValue("ExecuteTransitionState1",1)
        --character:GetStateMachine():ChangeState("Character","TransitionState2")
    end,
    Exit=function(character)
        --character:SetInternalValue("ExitTransitionState1",1)
    end
}
