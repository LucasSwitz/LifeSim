ScriptType = "State"
StateOwner = "Character"
StateName = "Global"

CharacterGlobalState = {
    Enter=function(character)
        print ("Entered Global")
    end,
    Execute=function(character)
        character:GetStateMachine():ChangeState("Character","Global");
    end,
    Exit=function(character)
    end
}