ScriptType = "State"
StateOwner = "Character"
StateName = "TransitionState2"

TransitionState2 = {    
    Enter=function(character)
        character:SetInternalValue("EnterTransitionState2",1)
    end,
    Execute=function(character)
        character:SetInternalValue("ExecuteTransitionState2",1)
    end,
    Exit=function(character)
        character:SetInternalValue("ExitTransitionState2",1)
    end
}