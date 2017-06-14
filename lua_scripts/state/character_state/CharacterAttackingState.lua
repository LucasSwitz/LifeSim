ScriptType = "State"
StateOwner = "Character"
StateName = "Attacking"

CharacterAttackingState = 
{
    StateName = 
    function Enter(character)
        character:AddAction("Attack")
    end,
    function Execute(character)
        if(character:GetCurrentAction:IsFinished())
            character:GetStateMachine:ChangeState("Character","Idle")
    end,
    function Exit(character)
    
    end
}